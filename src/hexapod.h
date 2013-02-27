

#ifndef hexapoda_hexapod_h
#define hexapoda_hexapod_h
#include "ofMain.h"



class hexapod {
public:
    
    // position of body
    ofVec3f bodyCenterPos;
    // translate position
    ofVec3f location;
    // rotation
    ofVec3f rotP;
    //velocity
    ofVec3f vel;
    //accleration
    ofVec3f acc;
    
    
    ofVec3f current, previous;
    
    ofPoint transPoint;
    //size
    float scale;
    float mass;
    
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
    float headFrontH;
    float headBackW;
    float headBackH;
    float headLen;
    float headOffset;
    float tailFrontW ;
    float tailFrontH ;
    float tailBackW ;
    float tailBackH ;
    float tailLen ;
    float tailOffset ;

    //Vertex
    vector<ofVec3f> bodyCenter, bodyHead, bodyTail, wings;
   //Meshes
    ofMesh meshBody, meshHead, meshTail, wingsVertexUP, wingsVertexDOWN;


    //Constructor
    hexapod();
    
    
    void addForce(ofVec3f);
    
    void update();
    
    void initMeshPoints();
    void updateMesh();
    void setNormals(ofMesh*);
    void setColors(ofMesh*);
    
    void draw();
    void drawNormals();
    void scaleMesh( float);
    
    void rotateToNormal(ofVec3f);
    void attToCenter();
   
    void slowDown();
    
    
    void updateMeshRadiusX(vector<ofVec3f>* , vector<ofVec3f>* , vector<ofVec3f>*);
    
    void updateMeshRadiusY(vector<ofVec3f>* , vector<ofVec3f>* , vector<ofVec3f>* );
    
    
    
    
    
    void setWings();
    
   
    
            
    float farbe;
       
    
        
    float radiusXScale;
    float radiusYScale;

};
#endif
