#pragma once

#include "ofxTweenTypeInterpolateArithmetic.h"
#include "ofxTweenTypeInterpolateColor.h"
#include "ofxTweenTypeInterpolateArray.h"
#include "ofxTweenTypeInterpolateQuaternion.h"
#include "ofxTweenTypeInterpolateMatrix.h"
#include "ofxTweenTypeInterpolateNode.h"
#include "ofxTweenTypeInterpolateCamera.h"

namespace ofx { namespace tweentype { namespace interpolate {
	template<typename Type> struct Typical { using type = Numeric<Type>; };
	template<typename PixelType> struct Typical<ofColor_<PixelType>> { using type = HSBColor<HueIPNear<ofColor_<PixelType>>>; };
	template<> struct Typical<ofQuaternion> { using type = QuaternionSpherical; };
	template<> struct Typical<node::Orbit> { using type = node::Orbit; };
	template<> struct Typical<ofNode> { using type = node::TRS; };
	template<> struct Typical<camera::Orbit> { using type = camera::Orbit; };
	template<> struct Typical<ofCamera> { using type = camera::Node<node::TRS>; };
	template<> struct Typical<ofMatrix4x4> { using type = Matrix4x4TRS; };
}}}
