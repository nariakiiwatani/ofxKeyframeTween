#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateQuaternion.h"

namespace ofx { namespace tweentype { namespace interpolate {

	struct Node {
		static inline int dim() { return 3; }
		static inline ofNode getInterpolated(float k, float k0, float k1, const ofNode &v0, const ofNode &v1, std::vector<ofEaseFunction> ease) {
			auto t = Numeric<ofVec3f>::getInterpolated(k, k0, k1, v0.getGlobalPosition(), v1.getGlobalPosition(), {ease[0]});
			auto r = QuaternionSpherical::getInterpolated(k, k0, k1, v0.getGlobalOrientation(), v1.getGlobalOrientation(), {ease[1]});
			auto s = Numeric<ofVec3f>::getInterpolated(k, k0, k1, v0.getGlobalScale(), v1.getGlobalScale(), {ease[2]});
			ofNode ret;
			ret.setPosition(t);
			ret.setOrientation(r);
			ret.setScale(s);
			return ret;
		}
	};
	
	template<> struct Typical<ofNode> { using type = Node; };
}}}
