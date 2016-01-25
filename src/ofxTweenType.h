//
//  ofxTweenType.h
//
//  Created by Iwatani Nariaki on 2016/01/22.
//
//

#pragma once

#include "ofxTweenLite.h"

namespace ofx { namespace keyframetween {
	
	template<typename Type>
	static Type tween(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease);
	
	template<>
	inline bool tween(float k, float k0, float k1, const bool &v0, const bool &v1, ofEaseFunction ease) {
		return ofxTweenLite::tween(v0?1:-1, v1?1:-1, ofMap(k,k0,k1,0,1), ease) >= 0;
	}
#define IMPL_ARITH(Type) \
	template<>\
	inline Type tween(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease) {\
		return ofxTweenLite::tween(v0, v1, ofMap(k,k0,k1,0,1), ease);\
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
#define IMPL_VEC(Type) \
	template<>\
	inline Type tween(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease) {\
		return v0.getInterpolated(v1, ofxTweenLite::tween(0, 1, ofMap(k,k0,k1,0,1), ease));\
	}
	IMPL_VEC(ofVec2f)
	IMPL_VEC(ofVec3f)
	IMPL_VEC(ofVec4f)
#undef IMPL_Vec
#define IMPL_COL(Type) \
	template<> \
	inline Type tween(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease) {\
		return v0.getLerped(v1, ofxTweenLite::tween(0, 1, ofMap(k,k0,k1,0,1), ease));\
	}
	IMPL_COL(ofColor)
	IMPL_COL(ofFloatColor)
	IMPL_COL(ofShortColor)
#undef IMPL_COL

	template<>
	inline ofQuaternion tween(float k, float k0, float k1, const ofQuaternion &v0, const ofQuaternion &v1, ofEaseFunction ease) {
		ofQuaternion ret;
		ret.slerp(ofxTweenLite::tween(0, 1, ofMap(k,k0,k1,0,1), ease), v0, v1);
		return ret;
	}
}}

template<typename Type>
inline Type ofxTweenType(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease)
{
	return ofx::keyframetween::tween<Type>(k,k0,k1,v0,v1,ease);
}


