#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"

namespace ofx { namespace tweentype { namespace interpolate {

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
}}}
