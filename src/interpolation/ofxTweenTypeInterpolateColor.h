#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"

namespace ofx { namespace tweentype { namespace interpolate {
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
	
}}}
