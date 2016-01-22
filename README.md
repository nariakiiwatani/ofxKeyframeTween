# ofxKeyframeTween

Tween types other than float

```
template<typename Type>
Type ofxTweenType(float k, float k0, float k1, const Type &v0, const Type &v1, ofEaseFunction ease);
```

and keyframe animation using the tween  
for example...

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

## Tested in
openFrameworks 0.9.0

## Dependencies
[ofxTweenLite](https://github.com/julapy/ofxTweenLite) by julapy

## License
MIT License.
