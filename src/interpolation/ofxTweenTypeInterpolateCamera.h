#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateNode.h"

namespace ofx { namespace tweentype { namespace interpolate {

	
	namespace camera {
		template<typename NodeIP>
		struct Node {
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
		struct Orbit {
			struct Param : public node::Orbit::Param {
				Param(){};
				Param(node::Orbit::Param &&p)
				:node::Orbit::Param(p)
				{}
				Param(const ofCamera &camera, ofVec3f lookat)
				:node::Orbit::Param(camera, lookat)
				,fov(camera.getFov())
				,aspect_ratio(camera.getAspectRatio())
				,near_clip(camera.getNearClip())
				,far_clip(camera.getFarClip())
				,lens_offset(camera.getLensOffset())
				{}
				float fov, near_clip, far_clip, aspect_ratio;
				ofVec2f lens_offset;
				void apply(ofCamera &camera) {
					node::Orbit::Param::apply(camera);
					camera.setFov(fov);
					camera.setAspectRatio(aspect_ratio);
					camera.setLensOffset(lens_offset);
					camera.setNearClip(near_clip);
					camera.setFarClip(far_clip);
				}
			};
			static int dim() { return node::Orbit::dim()+5; }
			static inline Param getInterpolated(float k, float k0, float k1, const Param &v0, const Param &v1, std::vector<ofEaseFunction> ease) {
				Param ret = node::Orbit::getInterpolated(k, k0, k1, v0, v1, ease);
				ret.fov = Numeric<float>::getInterpolated(k, k0, k1, v0.fov, v1.fov, {ease[node::Orbit::dim()+0]});
				ret.aspect_ratio = Numeric<float>::getInterpolated(k, k0, k1, v0.aspect_ratio, v1.aspect_ratio, {ease[node::Orbit::dim()+1]});
				ret.lens_offset = Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.lens_offset, v1.lens_offset, {ease[node::Orbit::dim()+2],ease[node::Orbit::dim()+2]});
				ret.near_clip = Numeric<float>::getInterpolated(k, k0, k1, v0.near_clip, v1.near_clip, {ease[node::Orbit::dim()+3]});
				ret.far_clip = Numeric<float>::getInterpolated(k, k0, k1, v0.far_clip, v1.far_clip, {ease[node::Orbit::dim()+4]});
				return ret;
			}
		};
	}

	template<> struct Typical<camera::Orbit::Param> { using type = camera::Orbit; };
	template<> struct Typical<ofCamera> { using type = camera::Node<node::TRS>; };
}}}
