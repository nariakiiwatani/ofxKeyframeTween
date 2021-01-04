#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateQuaternion.h"

namespace ofx { namespace tweentype { namespace interpolate {

	struct Matrix4x4TRS {
		static inline int dim() { return 3; }
		static inline ofMatrix4x4 getInterpolated(float k, float k0, float k1, const ofMatrix4x4 &v0, const ofMatrix4x4 &v1, std::vector<ofEaseFunction> ease) {
			ofVec3f t0,s0; ofQuaternion r0,sr0;
			ofVec3f t1,s1; ofQuaternion r1,sr1;
			ofVec3f t,s; ofQuaternion r;
			v0.decompose(t0, r0, s0, sr0);
			v1.decompose(t1, r1, s1, sr1);
			t = Numeric<ofVec3f>::getInterpolated(k, k0, k1, t0, t1, {ease[0],ease[0],ease[0]});
			r = QuaternionSpherical::getInterpolated(k, k0, k1, r0, r1, {ease[1],ease[1],ease[1],ease[1]});
			s = Numeric<ofVec3f>::getInterpolated(k, k0, k1, s0, s1, {ease[2],ease[2],ease[2]});
			ofMatrix4x4 ret;
			ret.makeIdentityMatrix();
			ret.scale(s);
			ret.rotate(r);
			ret.translate(t);
			return ret;
		}
	};
}}}
