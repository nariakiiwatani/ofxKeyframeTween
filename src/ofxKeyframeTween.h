#pragma once

#include "ofTypes.h"
#include "ofxTweenLite.h"
#include "ofxTweenType.h"

namespace ofx { namespace keyframetween {

	template<typename Value>
	class Keyframe : public std::map<float, pair<ofEaseFunction,Value>>
	{
	public:
		Value getValue(float key) {
			if(this->empty()) return Value();
			auto it0 = this->lower_bound(key);
			if(it0 == this->end()) return this->begin()->second.second;
			if(it0 == this->begin()) return it0->second.second;
			auto it1 = it0--;
			if(it0->second.first == -1) return it0->second.second;
			return ofxTweenType<Value>(key, it0->first, it1->first, it0->second.second, it1->second.second, it0->second.first);
		}
		bool addKeyFrame(float key, Value value, ofEaseFunction ease) {
			return this->insert(std::make_pair(key, std::make_pair(ease, value))).second;
		}
	};
	
}}
template<typename Value>
using ofxKeyframeTween = ofx::keyframetween::Keyframe<Value>;