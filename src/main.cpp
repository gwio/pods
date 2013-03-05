#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280,800, OF_WINDOW);			// <-------- setup the GL context
    window.setGlutDisplayString("rgba double samples>=2 depth");
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
    
}
