#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateNode.h"

namespace ofx { namespace tweentype { namespace interpolate {

	
	
	template<typename NodeIP>
	struct Camera {
		static inline int dim() { return NodeIP::dim()+5; }
		static inline ofCamera getInterpolated(float k, float k0, float k1, const ofCamera &v0, const ofCamera &v1, std::vector<ofEaseFunction> ease) {
			ofNode node = NodeIP::getInterpolated(k, k0, k1, v0, v1, ease);
			ofCamera ret;
			ret.setPosition(node.getPosition());
			ret.setOrientation(node.getOrientationQuat());
			ret.setScale(node.getScale());
			ret.setFov(Numeric<float>::getInterpolated(k, k0, k1, v0.getFov(), v1.getFov(), {ease[NodeIP::dim()+0]}));
			ret.setAspectRatio(Numeric<float>::getInterpolated(k, k0, k1, v0.getAspectRatio(), v1.getAspectRatio(), {ease[NodeIP::dim()+1]}));
			ret.setLensOffset(Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.getLensOffset(), v1.getLensOffset(), {ease[NodeIP::dim()+2],ease[NodeIP::dim()+2]}));
			ret.setNearClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getNearClip(), v1.getNearClip(), {ease[NodeIP::dim()+3]}));
			ret.setFarClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getFarClip(), v1.getFarClip(), {ease[NodeIP::dim()+4]}));
			return ret;
		}
	};
	template<> struct Typical<ofCamera> { using type = Camera<node::TRS>; };
}}}
