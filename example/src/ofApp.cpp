#include "ofApp.h"

#include "ofxKeyframeTween.h"

ofxKeyframeTween<ofQuaternion> tween;
//--------------------------------------------------------------
void ofApp::setup(){
	tween.addKeyFrame(0, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(1, ofQuaternion(90, ofVec3f(0,1,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(2, ofQuaternion(90, ofVec3f(0,1,1)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(3, ofQuaternion(180, ofVec3f(1,1,0)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(4, ofQuaternion(270, ofVec3f(1,0,1)), OF_EASE_CUBIC_IN);
	tween.addKeyFrame(5, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_CUBIC_IN);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
