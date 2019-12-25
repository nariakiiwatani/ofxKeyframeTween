#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"

namespace ofx { namespace tweentype { namespace interpolate {

	struct QuaternionSpherical {
		static inline int dim() { return 1; }
		static inline ofQuaternion getInterpolated(float k, float k0, float k1, const ofQuaternion &v0, const ofQuaternion &v1, std::vector<ofEaseFunction> ease) {
			ofQuaternion ret;
			ret.slerp(Numeric<float>::getInterpolated(k, k0, k1, 0, 1, {ease[0]}), v0, v1);
			return ret;
		}
	};
}}}
