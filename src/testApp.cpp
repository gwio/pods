#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    glEnable(GL_DEPTH_TEST); //make sure we test depth for 3d
    ofSetFrameRate(60);
    
    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_ALPHA));
    material.setShininess(10);
    material.setAmbientColor(33);
    material.setDiffuseColor(200);
    material.setSpecularColor(ofColor(111,111,111));
    
    
    
    light.enable();
    
    light.setAmbientColor(ofColor(19, 9, 9));
    light.setDiffuseColor(ofColor(222,222,222));
    light.setSpecularColor(ofColor(120,120,120));
    light.setPosition(0,550,0);
    
    
    
    cam.setDistance(100);
    cam.setPosition(0, 0, +100);
    
    cam.lookAt( ofVec3f(0,0,0));
    
    
    center.setPosition(0, 0, 0);
    
    for (int i=0; i < 50; i++) {
    animals.push_back(hexapod());
        animals[i].transPoint.x = i*30;
       // animals[i].initMeshPoints();
       // animals[i].updateMesh();
    }
    
   
}

//--------------------------------------------------------------
void testApp::update(){

    
    for (int i =0; i < animals.size(); i++) {
        animals[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    
    glEnable(GL_DEPTH_TEST);
    ofEnableLighting();
    material.begin();
    
    ofBackground(200, 200, 200);
    

    
    cam.begin();
    // light.draw();
    // center.draw();
    // cSystem();

    for (int i =0; i < animals.size(); i++) {
        animals[i].draw();
    }
    
    
    cam.end();
    material.end();
    glEnd();
    
    string fpsStr = ": "+ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, ofGetWidth()-100,100);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::guiEvent(ofxUIEventArgs &e) {
    
    string name = e.widget->getName();
	int kind = e.widget->getKind();

}

void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}

void testApp::cSystem() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 0, 0);
    
    
    ofLine(0, 0, 0, 0, 100, 0);
    
    ofSetColor(0, 255, 0);
    ofLine(0, 0, 0, 100, 0, 0);
    
    ofSetColor(0, 0, 255);
    ofLine(0, 0, 0, 0, 0, -100);
    
    ofPopStyle();
    
}