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
    ofNode center;
    
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    
    vector<hexapod> animals;
		
};
