#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	rot_.addKeyFrame(0, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_CUBIC_IN);
	rot_.addKeyFrame(1, ofQuaternion(90, ofVec3f(0,1,0)), OF_EASE_EXPO_IN);
	rot_.addKeyFrame(2, ofQuaternion(90, ofVec3f(0,1,1)), OF_EASE_CUBIC_IN);
	rot_.addKeyFrame(3, ofQuaternion(180, ofVec3f(1,1,0)), OF_EASE_BOUNCE_INOUT);
	rot_.addKeyFrame(4, ofQuaternion(270, ofVec3f(1,0,1)), OF_EASE_ELASTIC_INOUT);
	rot_.addKeyFrame(5, ofQuaternion(0, ofVec3f(1,0,0)), OF_EASE_EXPO_INOUT);

	color_.addKeyFrame(0, ofColor::white, OF_EASE_CUBIC_IN);
	color_.addKeyFrame(1, ofColor::red, OF_EASE_CUBIC_IN);
	color_.addKeyFrame(2, ofColor::green, OF_EASE_CUBIC_IN);
	color_.addKeyFrame(3, ofColor::blue, OF_EASE_CUBIC_IN);
	color_.addKeyFrame(4, ofColor::red, OF_EASE_CUBIC_IN);
	color_.addKeyFrame(5, ofColor::white, OF_EASE_CUBIC_IN);
	
	ofCamera camera;
	camera.setPosition(ofVec3f(0,0,100));
	camera.lookAt(ofVec3f(0,0,0));
	camera.setFov(60);
	camera.setAspectRatio(4/3.f);
	camera_.addKeyFrame(0, camera, OF_EASE_CUBIC_INOUT);
	camera.setFov(120);
	camera_.addKeyFrame(1, camera, OF_EASE_CUBIC_IN);
	camera.setPosition(ofVec3f(100,500,-200));
	camera.lookAt(ofVec3f(0,0,0));
	camera_.addKeyFrame(2, camera, OF_EASE_CUBIC_IN);
	camera.setPosition(ofVec3f(-100,50,200));
	camera.lookAt(ofVec3f(0,0,0));
	camera_.addKeyFrame(3, camera, OF_EASE_SINE_INOUT);
	camera.setAspectRatio(16/9.f);
	camera.setLensOffset(ofVec2f(0.5f,0));
	camera.setFov(60);
	camera_.addKeyFrame(4, camera, OF_EASE_CUBIC_IN);
	camera.setPosition(ofVec3f(0,0,100));
	camera.lookAt(ofVec3f(0,0,0));
	camera.setLensOffset(ofVec2f(0,0));
	camera_.addKeyFrame(5, camera, OF_EASE_BOUNCE_OUT);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	float timef = ofGetElapsedTimef();
	timef = ofWrap(timef,0,5);
	ofCamera camera = camera_.getValue(timef);
	camera.begin();
	ofPushMatrix();
	float d,x,y,z;
	rot_.getValue(timef).getRotate(d,x,y,z);
	ofRotate(d,x,y,z);
	ofPushStyle();
	ofSetColor(color_.getValue(timef));
	ofDrawRectangle(-50,-50, 100,100);
	ofPopStyle();
	ofPopMatrix();
	ofDrawAxis(100);
	camera.end();
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
