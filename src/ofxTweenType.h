#pragma once

#include "ofxTweenTypeInterpolation.h"

template<typename Type, typename Interpolator=typename ofx::tweentype::interpolate::Typical<Type>::type>
inline Type ofxTweenType(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease)
{
	std::vector<ofEaseFunction> eases(Interpolator::dim(), ease);
	return ofxTweenType<Type, Interpolator>(k,k0,k1,v0,v1,eases);
}

template<typename Type, typename Interpolator=typename ofx::tweentype::interpolate::Typical<Type>::type>
inline Type ofxTweenType(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease)
{
	if(ease.size() < Interpolator::dim()) {
		if(ease.empty()) {
			ease.emplace_back(OF_EASE_LINEAR_INOUT);
		}
		ease.insert(end(ease), Interpolator::dim()-ease.size(), ease.back());
	}
	return Interpolator::getInterpolated(k,k0,k1,v0,v1,ease);
}


