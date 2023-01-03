#include "ofApp.h"
#include "Nippo/Nippo.h"

//--------------------------------------------------------------
void ofApp::setup(){
    componentManager = make_shared<ofxComponentManager>();
    componentManager->addChild(make_shared<Nippo>());
    componentManager->setup();
    
    ofSetFrameRate(30);
    ofSetBackgroundColor(220);
    ofSetWindowTitle("Nippo");
    
    ofxFpsAutoReducer::setup(false);
    ofxFpsAutoReducer::setNormalFps(60);
    ofxFpsAutoReducer::addSleepSetting(ofxFpsAutoReducer::SleepSetting(0.5, 10));
    ofxFpsAutoReducer::addSleepSetting(ofxFpsAutoReducer::SleepSetting(10, 2));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // show fps
    //ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 0), 20, 20);
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
