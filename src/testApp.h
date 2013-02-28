#pragma once

#include "ofMain.h"
#include "hexapod.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
     void cSystem();
     ofEasyCam cam;
     ofMaterial material;
    ofLight light;
    ofLight light2;
    ofVec3f center;
    
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    
    vector<hexapod> animals;
    
    //forces
    float noiseInc, noiseX, noiseY, noiseZ;
   
    
    void updateWind();
    
    void attToCenter(vector<hexapod>*);
    
     void seperation(vector<hexapod>*);
    
    float windforce;
    ofVec3f wind;
    
    float globalSlow;
		
};
