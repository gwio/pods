#include "testApp.h"


#define PODS 50


//--------------------------------------------------------------
void testApp::setup(){
    glEnable(GL_DEPTH_TEST); //make sure we test depth for 3d
    ofSetFrameRate(60);
    
    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_ALPHA));
    material.setShininess(10);
    material.setAmbientColor(125);
    material.setDiffuseColor(30);
    material.setSpecularColor(ofColor(161,111,111));
    
    
    
    light.enable();
    light.setSpotlight();
    light.setSpotlightCutOff(50);
    light.setSpotConcentration(10);
    light.setAmbientColor(ofColor::fromHsb(190, 240, 170));
    light.setDiffuseColor(ofColor(33,55,55));
    light.setSpecularColor(ofColor(120,120,120));
    light.setPosition(0,800,0);
    
    
    light2.enable();
    
    light2.setAmbientColor(ofColor::fromHsb(140, 230, 130));
    light2.setDiffuseColor(ofColor(44,44,77));
    light2.setSpecularColor(ofColor(70,70,70));
    light2.setPosition(0,-100,0);
    
    
    cam.setFarClip(20000);
    cam.setNearClip(100);
   // cam.setFov();
   
    
    cam.setDistance(100);
    cam.setPosition(0, 0, +1000);
    
    cam.lookAt( ofVec3f(0,0,0));
    
    
    center = ofVec3f(0,0,0);
    globalSlow = 1.0;
    /*
     Constructor defintion ;)
     ofVec3f location_, ofVec3f startVel_, float bodyLen_, float bodyFrontH_, float bodyFrontW_,
     float bodyBackW_, float bodyBackH_, float bodyToHeadDist_, float bodyToTailDist_, float headFrontDia_,
     float headFrontDist_,float headLen_, float headFrontW_,
     float headFrontH_, float headBackW_, float headBackH_,float tailBackDia_, float tailBackDist_,
     float tailLen_, float tailFrontW_, float tailFrontH_,
     float tailBackW_, float tailBackH_, float* globalSlow, float scale_, ofColor farbe_)   
     */
    for (int i=0; i < PODS; i++) {
        animals.push_back(hexapod(
                ofVec3f(ofRandom(-200,200), ofRandom(-200,200), ofRandom(-200,200)),
                ofVec3f( ofRandom(-3,3), ofRandom(-200,200) , ofRandom(-3,3)),
                ofRandom(2,200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                
                ofRandom(-15, 200),
                ofRandom(-15, 200),
                
                ofRandom(2, 20),
                ofRandom(-30, 60),
                
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                
                ofRandom(2, 20),
                ofRandom(-30, 60),
                
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                ofRandom(2, 200),
                &globalSlow,
                
            1,
                ofColor::fromHsb(ofRandom(255), 30, 222, 180)
                ));
        
    }
    
    wind = ofVec3f(0,0,0);
 
    windforce = 0.1;
    
    //gui setup
    
    
    gui = new ofxUICanvas(0,0, 400, 900);
    
    gui->setFont("GUI/ssp_light.ttf");                     //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 8);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it.
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);
    gui->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui->setColorBack(ofColor(203,126,7,200));
    
    
    gui->addWidgetDown(new ofxUILabel("Settings", OFX_UI_FONT_SMALL));
    
    gui->addSpacer(0, 12);
    
    gui->addMinimalSlider ("VelSlow", 0.80, 1.2, 1.0);
    gui->addMinimalSlider("WindForce", 0.0, 1.0, 0.1);
//    gui->addMinimalSlider("HeadFrontH", 0.0, 100.0, 50 );
//    gui->addMinimalSlider("HeadBackW", 0.0, 100.0, 50);
//    gui->addMinimalSlider("HeadBackH", 0.0, 100.0, 50);
//    
//    gui->addSpacer(0, 12);
//    
//    gui->addMinimalSlider("BodyToHeadDia", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyToHeadDist", 0.0, 100.0, 50);
//    
//    gui->addSpacer(0, 12);
//    
//    gui->addMinimalSlider("BodyLen", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyFrontW", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyFrontH", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyBackW", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyBackH", 0.0, 100.0, 50);
//    
//    gui->addSpacer(0, 12);
//    
//    gui->addMinimalSlider("BodyToTailDia", 0.0, 100.0, 50);
//    gui->addMinimalSlider("BodyToTailDist", 0.0, 100.0, 50);
//    
//    gui->addSpacer(0, 12);
//    
//    gui->addMinimalSlider("TailLen", 0.0, 100.0, 50);
//    gui->addMinimalSlider("TailFrontW", 0.0, 100.0, 50);
//    gui->addMinimalSlider("TailFrontH", 0.0, 100.0, 50);
//    gui->addMinimalSlider("TailBackW", 0.0, 100.0, 50);
//    gui->addMinimalSlider("TailBackH", 0.0, 100.0, 50);
//    
//    gui->addMinimalSlider("RadiusX", -PI/4, PI/4, 0.0);
   // gui->addMinimalSlider("RadiusY", -PI/4, PI/4, 0.0);
    // gui->addMinimalSlider("Arc", 0, 360, arc);
    // gui->addMinimalSlider("InnerRadius", 0, 500, innerR);
    // gui->addMinimalSlider("OuterRadius", 0, 500, outerR);
    // gui->addMinimalSlider("Speed", -5.0, 5.0, rotSpeed);
    // gui->addMinimalSlider("Channel", 1, 16, channel);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
  //  gui->disable();
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
        
        if (distToCen > 1800) {
            dir.normalize();
            dir*=-1;
            dir*=((distToCen-1800)*0.00019);
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
                float dia = ((tiere_->at(i).lenTotal)  + ((tiere_->at(j).lenTotal))  )*6000;
                float dist = dir.lengthSquared();
                
                if ( dist < 125000+dia) {
                    
                    float force = (((125000+dia)/ dist) -1) *0.005;
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
    ofColor a1 = ofColor::fromHsb(170, 220, 50);
    ofColor a2 = ofColor::fromHsb(120, 180, 70);
    ofBackgroundGradient(a1 * 0.6, a2* 0.4);
    
        
    cam.begin();
    // light.draw();
    // center.draw();
     //cSystem();
    
    for (int i =0; i < animals.size(); i++) {
        animals[i].draw();
    }
    
    
    cam.end();
    material.end();
    glEnd();
    
    string fpsStr = "fps: "+ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, ofGetWidth()-100,100);
    
   // string windStr = "wind: "+ ofToString(wind.x);
   // ofDrawBitmapString(windStr, ofGetWidth()-100,200);
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
    
    
    if(name == "VelSlow")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        for(int i=0; i < animals.size(); i++) {
            animals[i].initMeshPoints();
            animals[i].velSlow = rslider->getScaledValue() ;
        }
	}
    
    else if (name == "WindForce")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
                    
           windforce = rslider->getScaledValue();
      
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
    float t = ( ofGetElapsedTimef())*0.1 ;
    
    wind.x = ofSignedNoise(t,0,0);
   wind.y = ofSignedNoise(0,t,0);
    wind.z = ofSignedNoise(0,0,t);
    
    wind*=windforce;
    
 
}