#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateNode.h"

namespace ofx { namespace tweentype { namespace interpolate {

	struct Camera {
		static inline int dim() { return 9; }
		static inline ofCamera getInterpolated(float k, float k0, float k1, const ofCamera &v0, const ofCamera &v1, std::vector<ofEaseFunction> ease) {
			ofNode node = Node::getInterpolated(k, k0, k1, v0, v1, ease);
			ofCamera ret;
			ret.setPosition(node.getPosition());
			ret.setOrientation(node.getOrientationQuat());
			ret.setScale(node.getScale());
			ret.setFov(Numeric<float>::getInterpolated(k, k0, k1, v0.getFov(), v1.getFov(), {ease[3]}));
			ret.setAspectRatio(Numeric<float>::getInterpolated(k, k0, k1, v0.getAspectRatio(), v1.getAspectRatio(), {ease[4]}));
			ret.setLensOffset(Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.getLensOffset(), v1.getLensOffset(), {ease[5],ease[6]}));
			ret.setNearClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getNearClip(), v1.getNearClip(), {ease[7]}));
			ret.setFarClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getFarClip(), v1.getFarClip(), {ease[8]}));
			return ret;
		}
	};
	template<> struct Typical<ofCamera> { using type = Camera; };
}}}
