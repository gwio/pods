#include "testApp.h"


#define PODS 65


//--------------------------------------------------------------
void testApp::setup(){
    glEnable(GL_DEPTH_TEST); //make sure we test depth for 3d
    ofSetFrameRate(60);
    
    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_ALPHA));
    material.setShininess(40);
    material.setAmbientColor(125);
    material.setDiffuseColor(30);
    material.setSpecularColor(ofColor(161,111,111));
    
    
    
    light.enable();
    light.setSpotlight();
    light.setSpotlightCutOff(50);
    light.setSpotConcentration(10);
    light.setAmbientColor(ofColor::fromHsb(30, 240, 170));
    light.setDiffuseColor(ofColor(33,55,55));
    light.setSpecularColor(ofColor(120,120,120));
    light.setPosition(0,800,0);
    
    
    light2.enable();
    
    light2.setAmbientColor(ofColor::fromHsb(25, 230, 130));
    light2.setDiffuseColor(ofColor(44,44,77));
    light2.setSpecularColor(ofColor(70,70,70));
    light2.setPosition(0,-300,0);
    
    
    cam.setFarClip(30000);
    cam.setNearClip(10);
    // cam.setFov();
    
    
    cam.setDistance(100);
    cam.setPosition(0, 0, 1000);
    
    // cam.lookAt( ofVec3f(0,0,0));
    
    
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
    float randomScale;
    for (int i=0; i < PODS; i++) {
        if ( i%10 == 0) {
            randomScale = 1.3;
        } else if (i%6 == 0){
            randomScale = 0.3;
            
        } else {
            
            randomScale = 0.9;
        }
        
        animals.push_back(hexapod(
                                  ofVec3f(ofRandom(-2000,2000), ofRandom(-2000,2000), ofRandom(-2000,2000)),
                                  ofVec3f( ofRandom(-3,3), ofRandom(-3,3), ofRandom(-3,3)),
                                  ofRandom(2,300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  
                                  ofRandom(-15, 200),
                                  ofRandom(-15, 200),
                                  
                                  ofRandom(2, 20),
                                  ofRandom(-30, 60),
                                  
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  
                                  ofRandom(2, 20),
                                  ofRandom(-30, 60),
                                  
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  ofRandom(2, 300),
                                  &globalSlow,
                                  
                                  randomScale,
                                  ofColor::fromHsb(ofRandom(255), 65, 112, 140),
                                  &wind
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
        animals[i].update();
    }
    
    
}

void testApp::attToCenter(vector<hexapod>* tiere_) {
    //float maxDist = 1000*1000*1000*1000;
    
    for (int i =0; i < tiere_->size(); i++) {
        
        ofVec3f dir = tiere_->at(i).location;
        dir - center;
        float distToCen = dir.length();
        
        if (distToCen > 2700) {
            dir.normalize();
            dir*=-1;
            dir*=((distToCen-2700)*0.00019);
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
                float dia = ((tiere_->at(i).lenTotal)  + ((tiere_->at(j).lenTotal))  )*6500;
                float dist = dir.lengthSquared();
                
                if ( dist < 125000+dia) {
                    
                    float force = (((125000+dia)/ dist) -1) *0.008;
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
    ofColor a1 = ofColor::fromHsb(40, 110, 30);
    ofColor a2 = ofColor::fromHsb(170, 130, 180);
    
    ofBackgroundGradient(a1 * 0.6, a2* 0.4);
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
    
        string fpsStr = "fps: "+ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapString(fpsStr, ofGetWidth()-100,100);
   
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
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'r':
            
            animals.clear();
            
            for (int i=0; i < PODS; i++) {
                
                animals.push_back(hexapod(
                                          ofVec3f(ofRandom(-200,200), ofRandom(-200,200), ofRandom(-200,200)),
                                          ofVec3f( ofRandom(-3,3), ofRandom(-3,3), ofRandom(-3,3)),
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
                                          
                                          0.4,
                                          ofColor::fromHsb(ofRandom(255), 65, 112, 140),
                                          
                                          &wind
                                          ));
                
                
            }
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
            globalSlow = rslider->getScaledValue() ;
        }
	}
    
    else if (name == "WindForce")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        
        windforce = rslider->getScaledValue();
        
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