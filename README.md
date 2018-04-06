# ofxKeyframeTween

We want to tween all types

```
template<typename Type, typename Interpolator>
Type ofxTweenType(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease);
```

## Keyframe animation

```
class ofApp {
	ofxKeyframeTween<ofQuaternion> tween;
};
void ofApp::setup() {
	tween.addKeyFrame(0, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(1, ofQuaternion(90, ofVec3f(0,1,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(2, ofQuaternion(90, ofVec3f(0,1,1)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(3, ofQuaternion(180, ofVec3f(1,1,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(4, ofQuaternion(270, ofVec3f(1,0,1)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(5, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_CUBIC_IN);
}
void ofApp::draw() {
	float timef = ofGetElapsedTimef();
	timef = ofWrap(timef,0,5);
	float d,x,y,z;
	tween.getValue(timef).getRotate(d,x,y,z);
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofRotate(d,x,y,z);
	ofDrawRectangle(-50,-50, 100,100);
	ofPopMatrix();
}
```

## Supported types
- char
- short
- int
- long
- long long
- unsigned char
- unsigned short
- unsigned int
- unsigned long
- unsigned long long
- float 
- double
- ofVec2f
- ofVec3f
- ofVec4f
- ofColor
- ofFloatColor
- ofShortColor
- ofQuaternion
- ofMatrix4x4
- ofNode
- ofCamera

## Advanced

### Change Interpolator

By default, ofxTwenType uses it's typical interpolation function.  
See `ofxTweenTypeInterpolators.h`'s `#pragma mark decide tipical functions`.  
You can change this as below,,,  

```
// this uses typical(based on TRS) interpolation
ofxTweenType<ofMatrix4x4>(...);
// change to numeric interpolation
ofxTweenType<ofMatrix4x4, ofx::tweentype::interpolate::Numeric<ofMatrix4x4>>(...);
```

### Custom Interpolator

You can write your custom Interpolators.  
You have to implement two functions on your Interpolator(struct). 

```
// object to tween
struct MyStruct {
	ofVec2f position;
	float rotation;
};
// your interpolator
struct MyInterpolator {
	static inline int dim() { return 2; }
	static inline MyStruct getInterpolated(float k, float k0, float k1, const MyStruct &v0, const MyStruct &v1, std::vector<ofEaseFunction> ease) {
		using namespace ofx::tweentype::interpolate;
		MyStruct ret;
		ret.position = Typical<ofVec2f>::type::getInterpolated(k, k0, k1, v0.position, v1.position, {ease[0]});
		ret.rotation = Typical<float>::type::getInterpolated(k, k0, k1, v0.rotation, v1.rotation, {ease[1]});
		return ret;
	}
};
// use it
float time;
MyStruct ms0,ms1;
MyStruct ms = ofxTweenType<MyStruct, MyInterpolator>(time, 0, 1, ms0, ms1, OF_EASE_CUBIC_IN);
```


## Tested in
openFrameworks 0.9.8

## Dependencies
[ofxTweenLite](https://github.com/julapy/ofxTweenLite) by julapy

## License
MIT License.

## Special Thanks
[2bbb](https://github.com/2bbb)