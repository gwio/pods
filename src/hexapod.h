

#ifndef hexapoda_hexapod_h
#define hexapoda_hexapod_h
#include "ofMain.h"



class hexapod {
public:
    
    /*
     ofVec3f location_, ofVec3f startVel_, float bodyLen_, float bodyFrontH_, float bodyFrontW_,
     float bodyBackW_, float bodyBackH_, float bodyToHeadDist_, float bodyToTailDist_, float headFrontDia_,
     float headFrontDist_,float headLen_, float headFrontW_,
     float headFrontH_, float headBackW_, float headBackH_,float tailBackDia_, float tailBackDist_,
     float tailLen_, float tailFrontW_, float tailFrontH_,
     float tailBackW_, float tailBackH_, float* globalSlow, float scale_, ofColor farbe_)
     */
    //Constructor
    hexapod(ofVec3f,ofVec3f, float, float, float, float, float, float, float, float, float, float, float, float,
            float, float, float, float, float, float, float, float, float, float*, float, ofColor
            );
    //----------------------------------------------
    
    // center of body
    ofVec3f bodyCenterPos;
    
    ////////motion_______________________
    
    // translate position
    ofVec3f location;
    ofPoint transPoint;
    // rotation
    ofVec3f rotP;
    //velocity
    ofVec3f vel;
    //accleration
    ofVec3f acc;
    float mass;
   
    
    //global Slowdown
    float* velSlow;
    
    
    //////////Form__________________________________
    //size
    float scale;
    //Vertex
    vector<ofVec3f> bodyCenter, bodyHead, bodyTail, wings;
    //Meshes
    ofMesh meshBody, meshHead, meshTail, wingsVertexUP, wingsVertexDOWN;
    
    
    //mesh description
    float lenTotal;
    float bodyToHeadDia;
    float bodyToHeadDist;
    float bodyToTailDia;
    float bodyToTailDist;
    float bodyFrontW;
    float bodyFrontH;
    float bodyBackW;
    float bodyBackH;
    float bodyLen;
    float headFrontW;
    float headFrontDist;
    float headFrontDia;
    float headFrontH;
    float headBackW;
    float headBackH;
    float headLen;
    float headOffset;
    float tailBackDist;
    float tailBackDia;
    float tailFrontW ;
    float tailFrontH ;
    float tailBackW ;
    float tailBackH ;
    float tailLen ;
    float tailOffset ;
    
    float farbe;
    
    float radiusXScale;
    float radiusYScale;
    
    
    // ______________________________________methods
    void draw();
    void update();
    
    //methods for polygon_____
    
    ////vector of points
    void initMeshPoints();
    //mesh
    void updateMesh();
    void setNormals(ofMesh*);
    void setColors(ofMesh*);
    void drawNormals();
    void scaleMesh(float);
    
    void setWings();
    
    //motion______
    void updateMeshRadiusX(vector<ofVec3f>* , vector<ofVec3f>* , vector<ofVec3f>*);
    void updateMeshRadiusY(vector<ofVec3f>* , vector<ofVec3f>* , vector<ofVec3f>* );
    void rotateToNormal();
    void slowDown();
    void addForce(ofVec3f);
    
    ///experimental
    
    
};
#endif
