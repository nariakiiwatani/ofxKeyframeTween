#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateQuaternion.h"

namespace ofx { namespace tweentype { namespace interpolate {

namespace node {
	struct TRS {
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
	
	struct Orbit {
		struct Param {
			Param(){}
			Param(const ofNode &node, ofVec3f lookat)
			:position(node.getGlobalPosition())
			,orientation(node.getGlobalOrientation())
			,scale(node.getGlobalScale())
			,lookat(lookat)
			,distance(position.distance(lookat))
			{}
			Param(ofVec3f position, ofQuaternion orientation, ofVec3f scale, ofVec3f lookat)
			:position(position)
			,orientation(orientation)
			,scale(scale)
			,lookat(lookat)
			,distance(position.distance(lookat))
			{}
			ofVec3f position;
			ofQuaternion orientation;
			ofVec3f scale;
			ofVec3f lookat;
			float distance;
			void apply(ofNode &node) {
				node.setGlobalPosition(position);
				node.setGlobalOrientation(orientation);
				node.setScale(scale);
				node.lookAt(lookat);
			}
		};
		static inline int dim() { return 3; }
		static inline Param getInterpolated(float k, float k0, float k1, const Param &v0, const Param &v1, std::vector<ofEaseFunction> ease) {
			auto lookat = Numeric<ofVec3f>::getInterpolated(k, k0, k1, v0.lookat, v1.lookat, {ease[0]});
			auto distance = Numeric<float>::getInterpolated(k, k0, k1, v0.distance, v1.distance, {ease[0]});
			auto r = QuaternionSpherical::getInterpolated(k, k0, k1, v0.orientation, v1.orientation, {ease[1]});
			auto s = Numeric<ofVec3f>::getInterpolated(k, k0, k1, v0.scale, v1.scale, {ease[2]});
			auto t = lookat + r*ofVec3f(0,0,distance);
			return {t,r,s,lookat};
		}
	};
}
	template<> struct Typical<node::Orbit::Param> { using type = node::Orbit; };
	template<> struct Typical<ofNode> { using type = node::TRS; };
}}}
