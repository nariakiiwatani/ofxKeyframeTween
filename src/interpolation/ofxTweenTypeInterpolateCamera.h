#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateNode.h"
#include "ofxKeyframeTweenUtils.h"

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
				ret.setFov(Numeric<float>::getInterpolated(k, k0, k1, v0.getFov(), v1.getFov(), utils::makeVectorFor<Numeric<float>>(ease[NodeIP::dim()+0])));
				ret.setAspectRatio(Numeric<float>::getInterpolated(k, k0, k1, v0.getAspectRatio(), v1.getAspectRatio(), utils::makeVectorFor<Numeric<float>>(ease[NodeIP::dim()+1])));
				ret.setLensOffset(Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.getLensOffset(), v1.getLensOffset(), utils::makeVectorFor<Numeric<ofVec2f>>(ease[NodeIP::dim()+2])));
				ret.setNearClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getNearClip(), v1.getNearClip(), utils::makeVectorFor<Numeric<float>>(ease[NodeIP::dim()+3])));
				ret.setFarClip(Numeric<float>::getInterpolated(k, k0, k1, v0.getFarClip(), v1.getFarClip(), utils::makeVectorFor<Numeric<float>>(ease[NodeIP::dim()+4])));
				return ret;
			}
		};
		struct Orbit : public node::Orbit {
			Orbit(){};
			Orbit(node::Orbit &&o)
			:node::Orbit(o)
			{}
			Orbit(node::Orbit &&o, float fov, float near_clip, float far_clip, float aspect_ratio, ofVec2f lens_offset)
			:node::Orbit(o)
			,fov(fov),near_clip(near_clip),far_clip(far_clip),aspect_ratio(aspect_ratio),lens_offset(lens_offset)
			{}
			Orbit(const ofCamera &camera, ofVec3f lookat)
			:Orbit(node::Orbit(camera, lookat)
				   ,camera.getFov()
				   ,camera.getNearClip()
				   ,camera.getFarClip()
				   ,camera.getAspectRatio()
				   ,camera.getLensOffset())
			{}
			Orbit(const ofCamera &camera, float distance)
			:Orbit(camera, camera.getGlobalPosition()+camera.getLookAtDir()*distance)
			{}
			float fov, near_clip, far_clip, aspect_ratio;
			ofVec2f lens_offset;
			void apply(ofCamera &camera) {
				node::Orbit::apply(camera);
				camera.setFov(fov);
				camera.setAspectRatio(aspect_ratio);
				camera.setLensOffset(lens_offset);
				camera.setNearClip(near_clip);
				camera.setFarClip(far_clip);
			}
			static int dim() { return node::Orbit::dim()+5; }
			static inline Orbit getInterpolated(float k, float k0, float k1, const Orbit &v0, const Orbit &v1, std::vector<ofEaseFunction> ease) {
				Orbit ret = node::Orbit::getInterpolated(k, k0, k1, v0, v1, ease);
				ret.fov = Numeric<float>::getInterpolated(k, k0, k1, v0.fov, v1.fov, utils::makeVectorFor<Numeric<float>>(ease[node::Orbit::dim()+0]));
				ret.aspect_ratio = Numeric<float>::getInterpolated(k, k0, k1, v0.aspect_ratio, v1.aspect_ratio, utils::makeVectorFor<Numeric<float>>(ease[node::Orbit::dim()+1]));
				ret.lens_offset = Numeric<ofVec2f>::getInterpolated(k, k0, k1, v0.lens_offset, v1.lens_offset, utils::makeVectorFor<Numeric<ofVec2f>>(ease[node::Orbit::dim()+2]));
				ret.near_clip = Numeric<float>::getInterpolated(k, k0, k1, v0.near_clip, v1.near_clip, utils::makeVectorFor<Numeric<float>>(ease[node::Orbit::dim()+3]));
				ret.far_clip = Numeric<float>::getInterpolated(k, k0, k1, v0.far_clip, v1.far_clip, utils::makeVectorFor<Numeric<float>>(ease[node::Orbit::dim()+4]));
				return ret;
			}
		};
	}
}}}
