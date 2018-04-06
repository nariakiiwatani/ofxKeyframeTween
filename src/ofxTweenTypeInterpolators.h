//
//  ofxTweenTypeInterpolators.h
//
//  Created by Iwatani Nariaki on 2018/04/05.
//
//

#pragma once

#include "ofxTweenLite.h"

namespace ofx { namespace tweentype { namespace interpolate {
	
#pragma mark Numeric
	
	template<typename Type>
	struct Numeric {
		static inline int dim();
		static inline Type getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease);
	};
	
	template<> inline int Numeric<bool>::dim() { return 1; }
	template<> inline bool Numeric<bool>::getInterpolated(float k, float k0, float k1, const bool &v0, const bool &v1, std::vector<ofEaseFunction> ease) {
		return ofxTweenLite::tween(v0?1:-1, v1?1:-1, ofMap(k,k0,k1,0,1), ease[0]) >= 0;
	}
#define IMPL_ARITH(Type) \
template<> inline int Numeric<Type>::dim() { return 1; } \
template<> inline Type Numeric<Type>::getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease) {\
return ofxTweenLite::tween(v0, v1, ofMap(k,k0,k1,0,1), ease[0]);\
}
	IMPL_ARITH(char)
	IMPL_ARITH(short)
	IMPL_ARITH(int)
	IMPL_ARITH(long)
	IMPL_ARITH(long long)
	IMPL_ARITH(unsigned char)
	IMPL_ARITH(unsigned short)
	IMPL_ARITH(unsigned int)
	IMPL_ARITH(unsigned long)
	IMPL_ARITH(unsigned long long)
	IMPL_ARITH(float)
	IMPL_ARITH(double)
#undef IMPL_ARITH
	
#define IMPL_ARRAY(Type, DIM) \
template<> inline int Numeric<Type>::dim() { return DIM; } \
template<> inline Type Numeric<Type>::getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease) {\
Type ret; for(int i = 0; i < DIM; ++i) { ret[i] = Numeric<float>::getInterpolated(k, k0, k1, v0[i], v1[i], {ease[i]}); } \
return ret; \
}
	IMPL_ARRAY(ofVec2f, 2)
	IMPL_ARRAY(ofVec3f, 3)
	IMPL_ARRAY(ofVec4f, 4)
	IMPL_ARRAY(ofColor, 4)
	IMPL_ARRAY(ofFloatColor, 4)
	IMPL_ARRAY(ofShortColor, 4)
	IMPL_ARRAY(ofQuaternion, 4)
#undef IMPL_ARRAY
	
#define IMPL_MATRIX(Type, DIM) \
	template<> inline int Numeric<Type>::dim() { return DIM; } \
	template<> inline Type Numeric<Type>::getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease) { \
		Type ret; auto p = ret.getPtr(); auto p0 = v0.getPtr(), p1 = v1.getPtr(); \
		for(int i = 0; i < DIM; ++i) { p[i] = Numeric<float>::getInterpolated(k, k0, k1, p0[i], p1[i], {ease[i]}); } \
		return ret; \
	}
//	IMPL_MATRIX(ofMatrix3x3, 9)	// ofMatrix3x3 is not so similar to 4x4 thing. so we can't impliment in the same way.
	IMPL_MATRIX(ofMatrix4x4, 16)
#undef IMPL_MATRIX
	
#pragma mark Quaternion
	
	struct QuaternionSpherical {
		static inline int dim() { return 1; }
		static inline ofQuaternion getInterpolated(float k, float k0, float k1, const ofQuaternion &v0, const ofQuaternion &v1, std::vector<ofEaseFunction> ease) {
			ofQuaternion ret;
			ret.slerp(Numeric<float>::getInterpolated(k, k0, k1, 0, 1, {ease[0]}), v0, v1);
			return ret;
		}
	};
	
#pragma mark Matrix
	
	struct Matrix4x4TRS {
		static inline int dim() { return 3; }
		static inline ofMatrix4x4 getInterpolated(float k, float k0, float k1, const ofMatrix4x4 &v0, const ofMatrix4x4 &v1, std::vector<ofEaseFunction> ease) {
			ofVec3f t0,s0; ofQuaternion r0,sr0;
			ofVec3f t1,s1; ofQuaternion r1,sr1;
			ofVec3f t,s; ofQuaternion r;
			v0.decompose(t0, r0, s0, sr0);
			v1.decompose(t1, r1, s1, sr1);
			t = Numeric<ofVec3f>::getInterpolated(k, k0, k1, t0, t1, {ease[0]});
			r = QuaternionSpherical::getInterpolated(k, k0, k1, r0, r1, {ease[1]});
			s = Numeric<ofVec3f>::getInterpolated(k, k0, k1, s0, s1, {ease[2]});
			ofMatrix4x4 ret;
			ret.makeIdentityMatrix();
			ret.scale(s);
			ret.rotate(r);
			ret.translate(t);
			return ret;
		}
	};
	
#pragma mark Node

	struct Node {
		static inline int dim() { return 3; }
		static inline ofNode getInterpolated(float k, float k0, float k1, const ofNode &v0, const ofNode &v1, std::vector<ofEaseFunction> ease) {
			ofMatrix4x4 mat = Matrix4x4TRS::getInterpolated(k, k0, k1, v0.getGlobalTransformMatrix(), v1.getGlobalTransformMatrix(), ease);
			ofNode ret;
			ret.setTransformMatrix(mat);
			return ret;
		}
	};

#pragma mark Camera
	
	struct Camera {
		static inline int dim() { return 9; }
		static inline ofCamera getInterpolated(float k, float k0, float k1, const ofCamera &v0, const ofCamera &v1, std::vector<ofEaseFunction> ease) {
			ofCamera ret;
			ret.setTransformMatrix(Matrix4x4TRS::getInterpolated(k, k0, k1, v0.getGlobalTransformMatrix(), v1.getGlobalTransformMatrix(), {ease[0],ease[1],ease[2]}));
			ret.setFov(Numeric<float>::getInterpolated(k, k0, k1, v0.getFov(), v1.getFov(), {ease[3]}));
			ret.setAspectRatio(Numeric<float>::getInterpolated(k, k0, k1, v0.getAspectRatio(), v1.getAspectRatio(), {ease[4]}));
			ret.setLensOffset(Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.getLensOffset(), v1.getLensOffset(), {ease[5],ease[6]}));
			ret.setNearClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getNearClip(), v1.getNearClip(), {ease[7]}));
			ret.setFarClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getFarClip(), v1.getFarClip(), {ease[8]}));
			return ret;
		}
	};
	
#pragma mark Color
	
	template<typename HueIP = Numeric<float>>
	struct HSBColor {
		static inline int dim() { return 4; }
		template<typename ColorType>
		static inline ColorType getInterpolated(float k, float k0, float k1, const ColorType &v0, const ColorType &v1, std::vector<ofEaseFunction> ease) {
			float h0,s0,b0,h1,s1,b1,h,s,b,a;
			v0.getHsb(h0,s0,b0);
			v1.getHsb(h1,s1,b1);
			h = HueIP::getInterpolated(k, k0, k1, h0, h1, {ease[0]});
			s = Numeric<float>::getInterpolated(k, k0, k1, s0, s1, {ease[1]});
			b = Numeric<float>::getInterpolated(k, k0, k1, b0, b1, {ease[2]});
			a = Numeric<float>::getInterpolated(k, k0, k1, v0.a, v1.a, {ease[3]});
			return ColorType::fromHsb(h,s,b,a);
		}
	};
	template<typename ColorType>
	struct HueIPNear {
		static inline int dim() { return 1; }
		static inline float getInterpolated(float k, float k0, float k1, const float &v0, const float &v1, std::vector<ofEaseFunction> ease) {
			float h0 = v0, h1 = v1;
			float sub = h1-h0;
			if(abs(sub) > ColorType::limit()/2.f) {
				if(sub > 0) h0 += ColorType::limit();
				else h1 += ColorType::limit();
			}
			return ofWrap(Numeric<float>::getInterpolated(k, k0, k1, h0, h1, {ease[0]}), 0, ColorType::limit());
		}
	};
	template<typename ColorType>
	struct HueIPFar {
		static inline int dim() { return 1; }
		static inline float getInterpolated(float k, float k0, float k1, const float &v0, const float &v1, std::vector<ofEaseFunction> ease) {
			float h0 = v0, h1 = v1;
			float sub = h1-h0;
			if(abs(sub) < ColorType::limit()/2.f) {
				if(sub > 0) h0 += ColorType::limit();
				else h1 += ColorType::limit();
			}
			return ofWrap(Numeric<float>::getInterpolated(k, k0, k1, h0, h1, {ease[0]}), 0, ColorType::limit());
		}
	};
	template<typename ColorType>
	struct HueIPUp {
		static inline int dim() { return 1; }
		static inline float getInterpolated(float k, float k0, float k1, const float &v0, const float &v1, std::vector<ofEaseFunction> ease) {
			float h0 = v0, h1 = v1;
			if(h1 < h0) h1 += ColorType::limit();
			return ofWrap(Numeric<float>::getInterpolated(k, k0, k1, h0, h1, {ease[0]}), 0, ColorType::limit());
		}
	};
	template<typename ColorType>
	struct HueIPDown {
		static inline int dim() { return 1; }
		static inline float getInterpolated(float k, float k0, float k1, const float &v0, const float &v1, std::vector<ofEaseFunction> ease) {
			float h0 = v0, h1 = v1;
			if(h0 < h1) h0 += ColorType::limit();
			return ofWrap(Numeric<float>::getInterpolated(k, k0, k1, h0, h1, {ease[0]}), 0, ColorType::limit());
		}
	};
	
#pragma mark decide tipical functions
	
	template<typename Type> struct Tipical { using type = Numeric<Type>; };
	template<> struct Tipical<ofQuaternion> { using type = QuaternionSpherical; };
	template<> struct Tipical<ofMatrix4x4> { using type = Matrix4x4TRS; };
	template<> struct Tipical<ofNode> { using type = Node; };
	template<> struct Tipical<ofCamera> { using type = Camera; };
	template<typename PixelType> struct Tipical<ofColor_<PixelType>> { using type = HSBColor<HueIPNear<ofColor_<PixelType>>>; };
}}}
