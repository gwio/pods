#include "testApp.h"


#define PODS 100


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
    
    
    cam.setFarClip(7000);
    
    cam.setDistance(100);
    cam.setPosition(0, 0, +1000);
    
    cam.lookAt( ofVec3f(0,0,0));
    
    
    center = ofVec3f(0,0,0);
    
    for (int i=0; i < PODS; i++) {
        animals.push_back(hexapod());
        if ((ofRandom(4)>3)) {
            
            //float scale = 3;
            animals[i].scaleMesh(3);
        } else {
            animals[i].scaleMesh(1);
        }
        
        
        // animals[i].initMeshPoints();
        // animals[i].updateMesh();
        
        
    }
    
    wind = ofVec3f(0,0,0);
 
   
    
    //gui setup
    
    
    gui = new ofxUICanvas(0,0, 400, 900);
    
    gui->setFont("GUI/ssp_light.ttf");                     //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 8);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it.
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);
    gui->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui->setColorBack(ofColor(203,126,7,200));
    
    
    gui->addWidgetDown(new ofxUILabel("Settings", OFX_UI_FONT_SMALL));
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider ("HeadLen", 0.0, 100.0, 50);
    gui->addMinimalSlider("HeadFrontW", 0.0, 100.0, 50);
    gui->addMinimalSlider("HeadFrontH", 0.0, 100.0, 50 );
    gui->addMinimalSlider("HeadBackW", 0.0, 100.0, 50);
    gui->addMinimalSlider("HeadBackH", 0.0, 100.0, 50);
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider("BodyToHeadDia", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyToHeadDist", 0.0, 100.0, 50);
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider("BodyLen", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyFrontW", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyFrontH", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyBackW", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyBackH", 0.0, 100.0, 50);
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider("BodyToTailDia", 0.0, 100.0, 50);
    gui->addMinimalSlider("BodyToTailDist", 0.0, 100.0, 50);
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider("TailLen", 0.0, 100.0, 50);
    gui->addMinimalSlider("TailFrontW", 0.0, 100.0, 50);
    gui->addMinimalSlider("TailFrontH", 0.0, 100.0, 50);
    gui->addMinimalSlider("TailBackW", 0.0, 100.0, 50);
    gui->addMinimalSlider("TailBackH", 0.0, 100.0, 50);
    
    gui->addMinimalSlider("RadiusX", -PI/4, PI/4, 0.0);
    gui->addMinimalSlider("RadiusY", -PI/4, PI/4, 0.0);
    // gui->addMinimalSlider("Arc", 0, 360, arc);
    // gui->addMinimalSlider("InnerRadius", 0, 500, innerR);
    // gui->addMinimalSlider("OuterRadius", 0, 500, outerR);
    // gui->addMinimalSlider("Speed", -5.0, 5.0, rotSpeed);
    // gui->addMinimalSlider("Channel", 1, 16, channel);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    updateWind();
    
    attToCenter(&animals);
    seperation(&animals);
    
    for (int i =0; i < animals.size(); i++) {
        animals[i].addForce(wind);
       // animals[i].addForce(ofVec3f(0,-0.4,0));
        animals[i].update();
    }
    
    
}

void testApp::attToCenter(vector<hexapod>* tiere_) {
    //float maxDist = 1000*1000*1000*1000;
    
    for (int i =0; i < tiere_->size(); i++) {
            
            ofVec3f dir = tiere_->at(i).location;
            dir - center;
        float distToCen = dir.length();
        
        if (distToCen > 1000) {
            dir.normalize();
            dir*=-1;
            dir*=((distToCen-1000)*0.00019);
            tiere_->at(i).addForce(dir);
            
        }
        
        
    }
}

void testApp::seperation(vector<hexapod>* tiere_) {
    
    for (int i = 0; i < tiere_->size(); i++) {
        for (int j= 0; j < tiere_->size(); j++) {
            
            if ( i != j) {
                ofVec3f dir = tiere_->at(i).location;
                dir-= tiere_->at(j).location;
                float dia = ((tiere_->at(i).bodyLen) + (tiere_->at(j).bodyLen))*5000;
                float dist = dir.lengthSquared();
                
                if ( dist < 15000+dia) {
                    
                    float force = (((15000+dia)/ dist) -1) *0.018;
                    dir.normalize();
                    dir*=force;
                    tiere_->at(i).addForce(dir);
                    dir*=-1;
                    tiere_->at(j).addForce(dir);
                }
                
            }
            
        }
    }
}
//--------------------------------------------------------------
void testApp::draw(){
    
    
    glEnable(GL_DEPTH_TEST);
    ofEnableLighting();
    material.begin();
    
    ofBackground(0, 0, 33);
    
    
    
    cam.begin();
    // light.draw();
    // center.draw();
     cSystem();
    
    for (int i =0; i < animals.size(); i++) {
        animals[i].draw();
    }
    
    
    cam.end();
    material.end();
    glEnd();
    
    string fpsStr = "fps: "+ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, ofGetWidth()-100,100);
    
    string windStr = "wind: "+ ofToString(wind.x);
    ofDrawBitmapString(windStr, ofGetWidth()-100,200);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key)
    {
        case 'g':
        {
            gui->toggleVisible();
            
        }
            break;
        default:
            break;
    }
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
    
    
    if(name == "HeadLen")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].headLen = rslider->getScaledValue() ;
        }
	}
    
    else if (name == "HeadFrontW")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].headFrontW = rslider->getScaledValue() ;
            
        }
	}
    
    else if (name == "HeadFrontH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].headFrontH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "HeadBackW")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].headBackW = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "HeadBackH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].headBackH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyToHeadDia")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyToHeadDia = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyToHeadDist")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyToHeadDist = rslider->getScaledValue() ;
            
        }
    }
    
    else if(name == "BodyLen")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyLen = rslider->getScaledValue() ;
            
        }
	}
    
    else if (name == "BodyFrontW")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyFrontW = rslider->getScaledValue() ;
            
        }
	}
    
    else if (name == "BodyFrontH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyFrontH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyBackW")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyBackW = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyBackH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyBackH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyToTailDia")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyToTailDia = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "BodyToTailDist")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].bodyToTailDist = rslider->getScaledValue() ;
            
        }
    }
    else if(name == "TailLen")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].tailLen = rslider->getScaledValue() ;
            
        }
	}
    
    else if (name == "TailFrontW")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].tailFrontW = rslider->getScaledValue() ;
            
        }
	}
    
    else if (name == "TailFrontH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].tailFrontH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "TailBackW")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].tailBackW = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "TailBackH")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].tailBackH = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "RadiusY")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].radiusYScale = rslider->getScaledValue() ;
            
        }
    }
    
    else if (name == "RadiusX")
    {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].radiusXScale = rslider->getScaledValue() ;
            
        }
    }
    
    
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

void testApp::updateWind() {
    

    //updateWind
    float t = ( ofGetElapsedTimef())*0.5 ;
    
    wind.x = ofSignedNoise(t,0,0);
    wind.y = ofSignedNoise(0,t,0);
    wind.z = ofSignedNoise(0,0,t);
    
    wind*=0.5;
    
 
}