

#include "hexapod.h"

//________________________________________________
hexapod::hexapod(ofVec3f location_, ofVec3f startVel_, float bodyLen_, float bodyFrontH_, float bodyFrontW_,
                 float bodyBackW_, float bodyBackH_, float bodyToHeadDist_, float bodyToTailDist_, float headFrontDia_,
                 float headFrontDist_,float headLen_, float headFrontW_,
                 float headFrontH_, float headBackW_, float headBackH_,float tailBackDia_, float tailBackDist_,
                 float tailLen_, float tailFrontW_, float tailFrontH_,
                 float tailBackW_, float tailBackH_, float* globalSlow_, float scale_, ofColor farbe_, ofVec3f* wind_) {
    
    
    //translate Position
    location = location_;
    //velo
    vel = startVel_;
    //accleration
    acc =ofVec3f(0,0,0);
    ///central POSITION
    bodyCenterPos = ofVec3f(0,0,0);
    //rotation
    rotP = ofVec3f(0,0,0);
    
    transPoint.set(location_.x,location_.y,location_.z);
    
    //______________________________________________________________________________ //body
    
    bodyToHeadDist = bodyToHeadDist_;
    bodyToTailDist = bodyToTailDist_;
    
    bodyFrontW = bodyFrontW_;
    bodyFrontH = bodyFrontH_;
    
    bodyBackW = bodyBackW_;
    bodyBackH = bodyBackH_;
    
    bodyLen = bodyLen_;
    
    bodyToTailDia = ofRandom(2, bodyLen_);
    bodyToHeadDia = ofRandom(2, bodyLen_);
    
    //_______________________________________________________________________________ //head
    headFrontW = headFrontW_;
    headFrontH = headFrontH_;
    
    headBackW = headBackW_;
    headBackH = headBackH_;
    
    headLen = headLen_;
    
    headFrontDia = headFrontDia_;
    headFrontDist = headFrontDist_;
    
    headOffset = (bodyLen/2) +(bodyToHeadDist) + (headLen/2);
    
    //_______________________________________________________________________ //tail
    tailFrontW = tailFrontW_;
    tailFrontH = tailFrontH_;
    
    tailBackW = tailBackW_;
    tailBackH = tailFrontH_;
    
    tailLen = tailLen_;
    
    tailBackDia = tailBackDia_;
    tailBackDist = tailBackDist_;
    
    tailOffset = (bodyLen/2) +(bodyToTailDist) + (tailLen/2);
    
    //------------ total length
    lenTotal = (headLen+bodyLen+tailLen+bodyToHeadDist+bodyToTailDist)*scale_;
    
    
    //defualt x and y deformation
    radiusYScale = 0.0;
    radiusXScale = 0.0;
    
    
    mass = scale_ ;
    
    farbe = farbe_;
    velSlow = globalSlow_;
    
    initMeshPoints();
    scaleMesh(scale_);
    updateMesh();
    
    trail.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    wind = wind_;
    
    grow = scale_;
    
    bufferSize = 40;
    for (int i = 0; i< bufferSize; i++) {
        pathVertices.push_back(location);
        velPath.push_back(vel);
    }
    
    
}


void hexapod::addForce(ofVec3f force_) {
    ofVec3f f = force_/mass;
    acc += f;
}

void hexapod::update() {
    
    // get new mesh points and scale
    initMeshPoints();
    //translate to the modelmatrix
    translateMeshPoints();
    //create the meshes
    updateMesh();
    
    
    
    vel += acc;
    slowDown();
    location += vel;
    
    // add the current position and velocity to stacks
    pathVertices.push_back(location);
    velPath.push_back(vel);
    
    akLocation = pathVertices[pathVertices.size()/2];
    akVel = velPath[velPath.size()/2];
    
    // if we have too many vertices in the deque, get rid of the oldest ones
    while(pathVertices.size() > bufferSize) {
        pathVertices.pop_front();
    }
    while(velPath.size() > bufferSize) {
        velPath.pop_front();
    }
    
    while(trailPoints.size() > 30) {
        trailPoints.pop_front();
    }
    
    if (ofGetFrameNum()%8 == 0) {
        trailPoints.push_back(bodyTail[20]);
        // trailPoints.push_back(pathVertices[0]);
    }
    
    
    trail.clear();
    for (int i=0; i < trailPoints.size(); i++) {
        trailPoints[i] += *wind*16*(i/4)+1;
        trailPoints[i].y += -3;
        trailPoints[i].z += ofRandom(-2,2);
        
        trail.addVertex(trailPoints[i]);
        
        
        trail.addColor(ofColor::fromHsb(farbe.getHue(),farbe.getSaturation()+20,farbe.getBrightness(), i*3));
    }
    
    setNormals(&trail);
    
    //reset accleration
    acc*=0;
    
    
    grow = sin ((ofGetElapsedTimef()/scale)*3) +1;
}



void hexapod::initMeshPoints() {
    
    
    bodyHead.clear();
    bodyCenter.clear();
    bodyTail.clear();
    
    
    headOffset = (bodyLen/2) +(bodyToHeadDist) + (headLen/2);
    tailOffset = (bodyLen/2) +(bodyToTailDist) + (tailLen/2);
    lenTotal = headLen+bodyLen+tailLen+(bodyToHeadDist)+(bodyToTailDist)+headFrontDist+tailBackDist;
    
    
    float tempA = bodyBackW;
    bodyBackW*= grow;
    
    
    //_________________________________________________________________________________________________ //bodyHead
    
    ///////VERTICES
    
    //top
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - ((headFrontW/3)/2) , bodyCenterPos.y + (headFrontH/2) , -headOffset + bodyCenterPos.z - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + ((headFrontW/3)/2) , bodyCenterPos.y + (headFrontH/2) , -headOffset + bodyCenterPos.z - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + ((headBackW/3)/2) , bodyCenterPos.y + (headBackH/2) , -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - ((headBackW/3)/2), bodyCenterPos.y + (headBackH/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + (headFrontW/2), bodyCenterPos.y + ((headFrontH/3)/2), -headOffset + bodyCenterPos.z  - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + (headBackW/2), bodyCenterPos.y + ((headBackH/3)/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - (headBackW/2), bodyCenterPos.y + ((headBackH/3)/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - (headFrontW/2), bodyCenterPos.y + ((headFrontH/3)/2), -headOffset + bodyCenterPos.z - (headLen/2) ) );
    //bottom
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - ((headFrontW/3)/2) , bodyCenterPos.y - (headFrontH/2) , -headOffset + bodyCenterPos.z - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + ((headFrontW/3)/2) , bodyCenterPos.y - (headFrontH/2) , -headOffset + bodyCenterPos.z - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + ((headBackW/3)/2) , bodyCenterPos.y - (headBackH/2) , -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - ((headBackW/3)/2), bodyCenterPos.y - (headBackH/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + (headFrontW/2), bodyCenterPos.y - ((headFrontH/3)/2), -headOffset +  bodyCenterPos.z  - (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x + (headBackW/2), bodyCenterPos.y - ((headBackH/3)/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - (headBackW/2), bodyCenterPos.y - ((headBackH/3)/2), -headOffset + bodyCenterPos.z + (headLen/2) ) );
    bodyHead.push_back( ofVec3f(bodyCenterPos.x - (headFrontW/2), bodyCenterPos.y - ((headFrontH/3)/2), -headOffset + bodyCenterPos.z - (headLen/2) ) );
    //front head end
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (headFrontDia), bodyCenterPos.y + (headFrontDia), -headOffset + bodyCenterPos.z - (headFrontDist) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (headFrontDia), bodyCenterPos.y + (headFrontDia), -headOffset + bodyCenterPos.z - (headFrontDist) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (headFrontDia), bodyCenterPos.y - (headFrontDia), -headOffset + bodyCenterPos.z - (headFrontDist) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (headFrontDia), bodyCenterPos.y - (headFrontDia), -headOffset + bodyCenterPos.z - (headFrontDist) - (headLen/2) ) );
    //back connection to body
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), -headOffset + bodyCenterPos.z + (bodyToHeadDist/2) + (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), -headOffset + bodyCenterPos.z + (bodyToHeadDist/2) + (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), -headOffset + bodyCenterPos.z + (bodyToHeadDist/2) + (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), -headOffset + bodyCenterPos.z + (bodyToHeadDist/2) + (headLen/2) ) );
    
    //_________________________________________________________________________________________________ //bodycenter
    
    
    
    
    /////VERTICES
    
    //top
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - ((bodyFrontW/3)/2) , bodyCenterPos.y + (bodyFrontH/2) , bodyCenterPos.z - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + ((bodyFrontW/3)/2) , bodyCenterPos.y + (bodyFrontH/2) , bodyCenterPos.z - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + ((bodyBackW/3)/2) , bodyCenterPos.y + (bodyBackH/2) , bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - ((bodyBackW/3)/2), bodyCenterPos.y + (bodyBackH/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + (bodyFrontW/2), bodyCenterPos.y + ((bodyFrontH/3)/2), bodyCenterPos.z  - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + (bodyBackW/2), bodyCenterPos.y + ((bodyBackH/3)/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - (bodyBackW/2), bodyCenterPos.y + ((bodyBackH/3)/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - (bodyFrontW/2), bodyCenterPos.y + ((bodyFrontH/3)/2), bodyCenterPos.z - (bodyLen/2) ) );
    //bottom
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - ((bodyFrontW/3)/2) , bodyCenterPos.y - (bodyFrontH/2) , bodyCenterPos.z - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + ((bodyFrontW/3)/2) , bodyCenterPos.y - (bodyFrontH/2) , bodyCenterPos.z - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + ((bodyBackW/3)/2) , bodyCenterPos.y - (bodyBackH/2) , bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - ((bodyBackW/3)/2), bodyCenterPos.y - (bodyBackH/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + (bodyFrontW/2), bodyCenterPos.y - ((bodyFrontH/3)/2), bodyCenterPos.z  - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x + (bodyBackW/2), bodyCenterPos.y - ((bodyBackH/3)/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - (bodyBackW/2), bodyCenterPos.y - ((bodyBackH/3)/2), bodyCenterPos.z + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f(bodyCenterPos.x - (bodyFrontW/2), bodyCenterPos.y - ((bodyFrontH/3)/2), bodyCenterPos.z - (bodyLen/2) ) );
    //front connection to head
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), bodyCenterPos.z - (bodyToHeadDist/2) - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), bodyCenterPos.z - (bodyToHeadDist/2) - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), bodyCenterPos.z - (bodyToHeadDist/2) - (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), bodyCenterPos.z - (bodyToHeadDist/2) - (bodyLen/2) ) );
    //back connection to tail
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), bodyCenterPos.z + (bodyToTailDist/2) + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), bodyCenterPos.z + (bodyToTailDist/2) + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), bodyCenterPos.z + (bodyToTailDist/2) + (bodyLen/2) ) );
    bodyCenter.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), bodyCenterPos.z + (bodyToTailDist/2) + (bodyLen/2) ) );
    
    
    
    //_________________________________________________________________________________________________ //bodyTail
    
    
    ///////VERTICES
    
    //top
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - ((tailFrontW/3)/2) , bodyCenterPos.y + (tailFrontH/2) , tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + ((tailFrontW/3)/2) , bodyCenterPos.y + (tailFrontH/2) , tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + ((tailBackW/3)/2) , bodyCenterPos.y + (tailBackH/2) , tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - ((tailBackW/3)/2), bodyCenterPos.y + (tailBackH/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + (tailFrontW/2), bodyCenterPos.y + ((tailFrontH/3)/2), tailOffset + bodyCenterPos.z  - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + (tailBackW/2), bodyCenterPos.y + ((tailBackH/3)/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - (tailBackW/2), bodyCenterPos.y + ((tailBackH/3)/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - (tailFrontW/2), bodyCenterPos.y + ((tailFrontH/3)/2), tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    //bottom
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - ((tailFrontW/3)/2) , bodyCenterPos.y - (tailFrontH/2) , tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + ((tailFrontW/3)/2) , bodyCenterPos.y - (tailFrontH/2) , tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + ((tailBackW/3)/2) , bodyCenterPos.y - (tailBackH/2) , tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - ((tailBackW/3)/2), bodyCenterPos.y - (tailBackH/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + (tailFrontW/2), bodyCenterPos.y - ((tailFrontH/3)/2), tailOffset +  bodyCenterPos.z  - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x + (tailBackW/2), bodyCenterPos.y - ((tailBackH/3)/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - (tailBackW/2), bodyCenterPos.y - ((tailBackH/3)/2), tailOffset + bodyCenterPos.z + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f(bodyCenterPos.x - (tailFrontW/2), bodyCenterPos.y - ((tailFrontH/3)/2), tailOffset + bodyCenterPos.z - (tailLen/2) ) );
    //front connection to Body
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), tailOffset + bodyCenterPos.z - (bodyToTailDist/2) - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), tailOffset + bodyCenterPos.z - (bodyToTailDist/2) - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), tailOffset + bodyCenterPos.z - (bodyToTailDist/2) - (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), tailOffset + bodyCenterPos.z - (bodyToTailDist/2) - (tailLen/2) ) );
    //tail end
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (tailBackDia), bodyCenterPos.y + (tailBackDia), tailOffset + bodyCenterPos.z + (tailBackDist) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (tailBackDia), bodyCenterPos.y + (tailBackDia), tailOffset + bodyCenterPos.z + (tailBackDist) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (tailBackDia), bodyCenterPos.y - (tailBackDia), tailOffset + bodyCenterPos.z + (tailBackDist) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (tailBackDia), bodyCenterPos.y - (tailBackDia), tailOffset + bodyCenterPos.z + (tailBackDist) + (tailLen/2) ) );
    
    scaleMesh(scale);
    
    bodyBackW = tempA;
    //bodyBackH = tempB;
}

void hexapod::translateMeshPoints() {
    
    //head _____
    
    ofPushMatrix();
    
    ofVec3f tempAngle = akLocation-location;
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight() );
    ofTranslate(akLocation.x, akLocation.y, akLocation.z);
    
    rotateToNormal(vel);
    
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    ofMatrix4x4 mat = m;
    
    
    for (int i= 0; i < bodyHead.size()-4; i++) {
        bodyHead[i] = bodyHead[i]*mat;
        bodyHead[i].y *= -1;
        
    }
    
    ofPopMatrix();
    
    //body_____________
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight() );
    ofTranslate(akLocation.x, akLocation.y, akLocation.z);
    rotateToNormal(akVel);
    
    
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    mat = m;
    
    for (int i= 0; i < bodyCenter.size(); i++) {
        bodyCenter[i] = bodyCenter[i]*mat;
        bodyCenter[i].y *= -1;
        
    }
    
    for (int i= bodyHead.size()-4; i < bodyHead.size(); i++) {
        bodyHead[i] = bodyHead[i]*mat;
        bodyHead[i].y *= -1;
    }
    
    for (int i= 16; i <= 19; i++) {
        bodyTail[i] = bodyTail[i]*mat;
        bodyTail[i].y *= -1;
    }
    
    ofPopMatrix();
    
    
    //tail______
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight() );
    ofTranslate(akLocation.x, akLocation.y, akLocation.z);
    
    
    rotateToNormal(velPath[0]);
    
    // rotateToNormal(akVel);
    
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    mat = m;
    
    for (int i= 0; i <= 15; i++) {
        bodyTail[i] = bodyTail[i]*mat;
        bodyTail[i].y *= -1;
    }
    
    for (int i= 20; i <= bodyTail.size()-1; i++) {
        bodyTail[i] = bodyTail[i]*mat;
        bodyTail[i].y *= -1;
    }
    
    
    
    
    
    ofPopMatrix();
    
}

void hexapod::updateMesh() {
    //set meshes and normals
    
    meshHead.clear();
    meshBody.clear();
    meshTail.clear();
    
    
    ///Head
    
    ////////TRIANGLES/////////
    
    //top center
    meshHead.addVertex(bodyHead[0]);
    meshHead.addVertex(bodyHead[1]);
    meshHead.addVertex(bodyHead[3]);
    
    meshHead.addVertex(bodyHead[3]);
    meshHead.addVertex(bodyHead[1]);
    meshHead.addVertex(bodyHead[2]);
    
    //top right
    meshHead.addVertex(bodyHead[2]);
    meshHead.addVertex(bodyHead[1]);
    meshHead.addVertex(bodyHead[4]);
    
    meshHead.addVertex(bodyHead[4]);
    meshHead.addVertex(bodyHead[5]);
    meshHead.addVertex(bodyHead[2]);
    
    //top left
    meshHead.addVertex(bodyHead[6]);
    meshHead.addVertex(bodyHead[7]);
    meshHead.addVertex(bodyHead[0]);
    
    meshHead.addVertex(bodyHead[0]);
    meshHead.addVertex(bodyHead[3]);
    meshHead.addVertex(bodyHead[6]);
    
    //bottom center
    meshHead.addVertex(bodyHead[9]);
    meshHead.addVertex(bodyHead[8]);
    meshHead.addVertex(bodyHead[11]);
    
    meshHead.addVertex(bodyHead[11]);
    meshHead.addVertex(bodyHead[10]);
    meshHead.addVertex(bodyHead[9]);
    
    //bottom right
    meshHead.addVertex(bodyHead[9]);
    meshHead.addVertex(bodyHead[10]);
    meshHead.addVertex(bodyHead[13]);
    
    meshHead.addVertex(bodyHead[13]);
    meshHead.addVertex(bodyHead[12]);
    meshHead.addVertex(bodyHead[9]);
    
    //bottom left
    meshHead.addVertex(bodyHead[8]);
    meshHead.addVertex(bodyHead[15]);
    meshHead.addVertex(bodyHead[14]);
    
    meshHead.addVertex(bodyHead[14]);
    meshHead.addVertex(bodyHead[11]);
    meshHead.addVertex(bodyHead[8]);
    
    //right center
    meshHead.addVertex(bodyHead[5]);
    meshHead.addVertex(bodyHead[4]);
    meshHead.addVertex(bodyHead[12]);
    
    meshHead.addVertex(bodyHead[12]);
    meshHead.addVertex(bodyHead[13]);
    meshHead.addVertex(bodyHead[5]);
    
    //left center
    meshHead.addVertex(bodyHead[7]);
    meshHead.addVertex(bodyHead[6]);
    meshHead.addVertex(bodyHead[14]);
    
    meshHead.addVertex(bodyHead[14]);
    meshHead.addVertex(bodyHead[15]);
    meshHead.addVertex(bodyHead[7]);
    
    
    
    
    // front head top, right, bottom, left
    meshHead.addVertex(bodyHead[1]);
    meshHead.addVertex(bodyHead[0]);
    meshHead.addVertex(bodyHead[16]);
    
    meshHead.addVertex(bodyHead[16]);
    meshHead.addVertex(bodyHead[17]);
    meshHead.addVertex(bodyHead[1]);
    
    meshHead.addVertex(bodyHead[12]);
    meshHead.addVertex(bodyHead[4]);
    meshHead.addVertex(bodyHead[17]);
    
    meshHead.addVertex(bodyHead[17]);
    meshHead.addVertex(bodyHead[18]);
    meshHead.addVertex(bodyHead[12]);
    
    meshHead.addVertex(bodyHead[8]);
    meshHead.addVertex(bodyHead[9]);
    meshHead.addVertex(bodyHead[18]);
    
    meshHead.addVertex(bodyHead[18]);
    meshHead.addVertex(bodyHead[19]);
    meshHead.addVertex(bodyHead[8]);
    
    meshHead.addVertex(bodyHead[19]);
    meshHead.addVertex(bodyHead[16]);
    meshHead.addVertex(bodyHead[7]);
    
    meshHead.addVertex(bodyHead[7]);
    meshHead.addVertex(bodyHead[15]);
    meshHead.addVertex(bodyHead[19]);
    
    
    // front head connection side triangles clockwise
    meshHead.addVertex(bodyHead[16]);
    meshHead.addVertex(bodyHead[0]);
    meshHead.addVertex(bodyHead[7]);
    
    meshHead.addVertex(bodyHead[1]);
    meshHead.addVertex(bodyHead[17]);
    meshHead.addVertex(bodyHead[4]);
    
    meshHead.addVertex(bodyHead[9]);
    meshHead.addVertex(bodyHead[12]);
    meshHead.addVertex(bodyHead[18]);
    
    meshHead.addVertex(bodyHead[19]);
    meshHead.addVertex(bodyHead[15]);
    meshHead.addVertex(bodyHead[8]);
    
    
    
    // back connection to body,  top, right, bottom, left
    meshHead.addVertex(bodyHead[3]);
    meshHead.addVertex(bodyHead[2]);
    meshHead.addVertex(bodyHead[21]);
    
    meshHead.addVertex(bodyHead[21]);
    meshHead.addVertex(bodyHead[20]);
    meshHead.addVertex(bodyHead[3]);
    
    meshHead.addVertex(bodyHead[22]);
    meshHead.addVertex(bodyHead[21]);
    meshHead.addVertex(bodyHead[5]);
    
    meshHead.addVertex(bodyHead[5]);
    meshHead.addVertex(bodyHead[13]);
    meshHead.addVertex(bodyHead[22]);
    
    meshHead.addVertex(bodyHead[23]);
    meshHead.addVertex(bodyHead[22]);
    meshHead.addVertex(bodyHead[10]);
    
    meshHead.addVertex(bodyHead[10]);
    meshHead.addVertex(bodyHead[11]);
    meshHead.addVertex(bodyHead[23]);
    
    meshHead.addVertex(bodyHead[6]);
    meshHead.addVertex(bodyHead[20]);
    meshHead.addVertex(bodyHead[23]);
    
    meshHead.addVertex(bodyHead[23]);
    meshHead.addVertex(bodyHead[14]);
    meshHead.addVertex(bodyHead[6]);
    
    
    // back connection to body, side triangles clockwise
    meshHead.addVertex(bodyHead[21]);
    meshHead.addVertex(bodyHead[2]);
    meshHead.addVertex(bodyHead[5]);
    
    meshHead.addVertex(bodyHead[22]);
    meshHead.addVertex(bodyHead[13]);
    meshHead.addVertex(bodyHead[10]);
    
    meshHead.addVertex(bodyHead[14]);
    meshHead.addVertex(bodyHead[23]);
    meshHead.addVertex(bodyHead[11]);
    
    meshHead.addVertex(bodyHead[6]);
    meshHead.addVertex(bodyHead[3]);
    meshHead.addVertex(bodyHead[20]);
    
    
    //close head triangle
    meshHead.addVertex(bodyHead[18]);
    meshHead.addVertex(bodyHead[17]);
    meshHead.addVertex(bodyHead[16]);
    
    meshHead.addVertex(bodyHead[16]);
    meshHead.addVertex(bodyHead[19]);
    meshHead.addVertex(bodyHead[18]);
    
    
    
    setNormals(&meshHead);
    
    setColors(&meshHead);
    
    //Body
    
    //TRIANGLES////////
    
    //top center
    meshBody.addVertex(bodyCenter[0]);
    meshBody.addVertex(bodyCenter[1]);
    meshBody.addVertex(bodyCenter[3]);
    
    meshBody.addVertex(bodyCenter[3]);
    meshBody.addVertex(bodyCenter[1]);
    meshBody.addVertex(bodyCenter[2]);
    
    //top right
    meshBody.addVertex(bodyCenter[2]);
    meshBody.addVertex(bodyCenter[1]);
    meshBody.addVertex(bodyCenter[4]);
    
    meshBody.addVertex(bodyCenter[4]);
    meshBody.addVertex(bodyCenter[5]);
    meshBody.addVertex(bodyCenter[2]);
    
    //top left
    meshBody.addVertex(bodyCenter[6]);
    meshBody.addVertex(bodyCenter[7]);
    meshBody.addVertex(bodyCenter[0]);
    
    meshBody.addVertex(bodyCenter[0]);
    meshBody.addVertex(bodyCenter[3]);
    meshBody.addVertex(bodyCenter[6]);
    
    //bottom center
    meshBody.addVertex(bodyCenter[9]);
    meshBody.addVertex(bodyCenter[8]);
    meshBody.addVertex(bodyCenter[11]);
    
    meshBody.addVertex(bodyCenter[11]);
    meshBody.addVertex(bodyCenter[10]);
    meshBody.addVertex(bodyCenter[9]);
    
    //bottom right
    meshBody.addVertex(bodyCenter[9]);
    meshBody.addVertex(bodyCenter[10]);
    meshBody.addVertex(bodyCenter[13]);
    
    meshBody.addVertex(bodyCenter[13]);
    meshBody.addVertex(bodyCenter[12]);
    meshBody.addVertex(bodyCenter[9]);
    
    //bottom left
    meshBody.addVertex(bodyCenter[8]);
    meshBody.addVertex(bodyCenter[15]);
    meshBody.addVertex(bodyCenter[14]);
    
    meshBody.addVertex(bodyCenter[14]);
    meshBody.addVertex(bodyCenter[11]);
    meshBody.addVertex(bodyCenter[8]);
    
    //right center
    meshBody.addVertex(bodyCenter[5]);
    meshBody.addVertex(bodyCenter[4]);
    meshBody.addVertex(bodyCenter[12]);
    
    meshBody.addVertex(bodyCenter[12]);
    meshBody.addVertex(bodyCenter[13]);
    meshBody.addVertex(bodyCenter[5]);
    
    //left center
    meshBody.addVertex(bodyCenter[7]);
    meshBody.addVertex(bodyCenter[6]);
    meshBody.addVertex(bodyCenter[14]);
    
    meshBody.addVertex(bodyCenter[14]);
    meshBody.addVertex(bodyCenter[15]);
    meshBody.addVertex(bodyCenter[7]);
    
    
    
    
    // front connection top, right, bottom, left
    meshBody.addVertex(bodyCenter[1]);
    meshBody.addVertex(bodyCenter[0]);
    meshBody.addVertex(bodyCenter[16]);
    
    meshBody.addVertex(bodyCenter[16]);
    meshBody.addVertex(bodyCenter[17]);
    meshBody.addVertex(bodyCenter[1]);
    
    meshBody.addVertex(bodyCenter[12]);
    meshBody.addVertex(bodyCenter[4]);
    meshBody.addVertex(bodyCenter[17]);
    
    meshBody.addVertex(bodyCenter[17]);
    meshBody.addVertex(bodyCenter[18]);
    meshBody.addVertex(bodyCenter[12]);
    
    meshBody.addVertex(bodyCenter[8]);
    meshBody.addVertex(bodyCenter[9]);
    meshBody.addVertex(bodyCenter[18]);
    
    meshBody.addVertex(bodyCenter[18]);
    meshBody.addVertex(bodyCenter[19]);
    meshBody.addVertex(bodyCenter[8]);
    
    meshBody.addVertex(bodyCenter[19]);
    meshBody.addVertex(bodyCenter[16]);
    meshBody.addVertex(bodyCenter[7]);
    
    meshBody.addVertex(bodyCenter[7]);
    meshBody.addVertex(bodyCenter[15]);
    meshBody.addVertex(bodyCenter[19]);
    
    
    // front connection side triangles clockwise
    meshBody.addVertex(bodyCenter[16]);
    meshBody.addVertex(bodyCenter[0]);
    meshBody.addVertex(bodyCenter[7]);
    
    meshBody.addVertex(bodyCenter[1]);
    meshBody.addVertex(bodyCenter[17]);
    meshBody.addVertex(bodyCenter[4]);
    
    meshBody.addVertex(bodyCenter[9]);
    meshBody.addVertex(bodyCenter[12]);
    meshBody.addVertex(bodyCenter[18]);
    
    meshBody.addVertex(bodyCenter[19]);
    meshBody.addVertex(bodyCenter[15]);
    meshBody.addVertex(bodyCenter[8]);
    
    
    
    // back connectrion top, right, bottom, left
    meshBody.addVertex(bodyCenter[3]);
    meshBody.addVertex(bodyCenter[2]);
    meshBody.addVertex(bodyCenter[21]);
    
    meshBody.addVertex(bodyCenter[21]);
    meshBody.addVertex(bodyCenter[20]);
    meshBody.addVertex(bodyCenter[3]);
    
    meshBody.addVertex(bodyCenter[22]);
    meshBody.addVertex(bodyCenter[21]);
    meshBody.addVertex(bodyCenter[5]);
    
    meshBody.addVertex(bodyCenter[5]);
    meshBody.addVertex(bodyCenter[13]);
    meshBody.addVertex(bodyCenter[22]);
    
    meshBody.addVertex(bodyCenter[23]);
    meshBody.addVertex(bodyCenter[22]);
    meshBody.addVertex(bodyCenter[10]);
    
    meshBody.addVertex(bodyCenter[10]);
    meshBody.addVertex(bodyCenter[11]);
    meshBody.addVertex(bodyCenter[23]);
    
    meshBody.addVertex(bodyCenter[6]);
    meshBody.addVertex(bodyCenter[20]);
    meshBody.addVertex(bodyCenter[23]);
    
    meshBody.addVertex(bodyCenter[23]);
    meshBody.addVertex(bodyCenter[14]);
    meshBody.addVertex(bodyCenter[6]);
    
    
    // back connection side triangles clockwise
    meshBody.addVertex(bodyCenter[21]);
    meshBody.addVertex(bodyCenter[2]);
    meshBody.addVertex(bodyCenter[5]);
    
    meshBody.addVertex(bodyCenter[22]);
    meshBody.addVertex(bodyCenter[13]);
    meshBody.addVertex(bodyCenter[10]);
    
    meshBody.addVertex(bodyCenter[14]);
    meshBody.addVertex(bodyCenter[23]);
    meshBody.addVertex(bodyCenter[11]);
    
    meshBody.addVertex(bodyCenter[6]);
    meshBody.addVertex(bodyCenter[3]);
    meshBody.addVertex(bodyCenter[20]);
    
    
    
    setNormals(&meshBody);
    
    setColors(&meshBody);
    
    
    //Tail
    ////////TRIANGLES/////////
    
    //top center
    meshTail.addVertex(bodyTail[0]);
    meshTail.addVertex(bodyTail[1]);
    meshTail.addVertex(bodyTail[3]);
    
    meshTail.addVertex(bodyTail[3]);
    meshTail.addVertex(bodyTail[1]);
    meshTail.addVertex(bodyTail[2]);
    
    //top right
    meshTail.addVertex(bodyTail[2]);
    meshTail.addVertex(bodyTail[1]);
    meshTail.addVertex(bodyTail[4]);
    
    meshTail.addVertex(bodyTail[4]);
    meshTail.addVertex(bodyTail[5]);
    meshTail.addVertex(bodyTail[2]);
    
    //top left
    meshTail.addVertex(bodyTail[6]);
    meshTail.addVertex(bodyTail[7]);
    meshTail.addVertex(bodyTail[0]);
    
    meshTail.addVertex(bodyTail[0]);
    meshTail.addVertex(bodyTail[3]);
    meshTail.addVertex(bodyTail[6]);
    
    //bottom center
    meshTail.addVertex(bodyTail[9]);
    meshTail.addVertex(bodyTail[8]);
    meshTail.addVertex(bodyTail[11]);
    
    meshTail.addVertex(bodyTail[11]);
    meshTail.addVertex(bodyTail[10]);
    meshTail.addVertex(bodyTail[9]);
    
    //bottom right
    meshTail.addVertex(bodyTail[9]);
    meshTail.addVertex(bodyTail[10]);
    meshTail.addVertex(bodyTail[13]);
    
    meshTail.addVertex(bodyTail[13]);
    meshTail.addVertex(bodyTail[12]);
    meshTail.addVertex(bodyTail[9]);
    
    //bottom left
    meshTail.addVertex(bodyTail[8]);
    meshTail.addVertex(bodyTail[15]);
    meshTail.addVertex(bodyTail[14]);
    
    meshTail.addVertex(bodyTail[14]);
    meshTail.addVertex(bodyTail[11]);
    meshTail.addVertex(bodyTail[8]);
    
    //right center
    meshTail.addVertex(bodyTail[5]);
    meshTail.addVertex(bodyTail[4]);
    meshTail.addVertex(bodyTail[12]);
    
    meshTail.addVertex(bodyTail[12]);
    meshTail.addVertex(bodyTail[13]);
    meshTail.addVertex(bodyTail[5]);
    
    //left center
    meshTail.addVertex(bodyTail[7]);
    meshTail.addVertex(bodyTail[6]);
    meshTail.addVertex(bodyTail[14]);
    
    meshTail.addVertex(bodyTail[14]);
    meshTail.addVertex(bodyTail[15]);
    meshTail.addVertex(bodyTail[7]);
    
    
    
    
    // front body connection top, right, bottom, left
    meshTail.addVertex(bodyTail[1]);
    meshTail.addVertex(bodyTail[0]);
    meshTail.addVertex(bodyTail[16]);
    
    meshTail.addVertex(bodyTail[16]);
    meshTail.addVertex(bodyTail[17]);
    meshTail.addVertex(bodyTail[1]);
    
    meshTail.addVertex(bodyTail[12]);
    meshTail.addVertex(bodyTail[4]);
    meshTail.addVertex(bodyTail[17]);
    
    meshTail.addVertex(bodyTail[17]);
    meshTail.addVertex(bodyTail[18]);
    meshTail.addVertex(bodyTail[12]);
    
    meshTail.addVertex(bodyTail[8]);
    meshTail.addVertex(bodyTail[9]);
    meshTail.addVertex(bodyTail[18]);
    
    meshTail.addVertex(bodyTail[18]);
    meshTail.addVertex(bodyTail[19]);
    meshTail.addVertex(bodyTail[8]);
    
    meshTail.addVertex(bodyTail[19]);
    meshTail.addVertex(bodyTail[16]);
    meshTail.addVertex(bodyTail[7]);
    
    meshTail.addVertex(bodyTail[7]);
    meshTail.addVertex(bodyTail[15]);
    meshTail.addVertex(bodyTail[19]);
    
    
    // front body connection side triangles clockwise
    meshTail.addVertex(bodyTail[16]);
    meshTail.addVertex(bodyTail[0]);
    meshTail.addVertex(bodyTail[7]);
    
    meshTail.addVertex(bodyTail[1]);
    meshTail.addVertex(bodyTail[17]);
    meshTail.addVertex(bodyTail[4]);
    
    meshTail.addVertex(bodyTail[9]);
    meshTail.addVertex(bodyTail[12]);
    meshTail.addVertex(bodyTail[18]);
    
    meshTail.addVertex(bodyTail[19]);
    meshTail.addVertex(bodyTail[15]);
    meshTail.addVertex(bodyTail[8]);
    
    
    
    // back tail end,  top, right, bottom, left
    meshTail.addVertex(bodyTail[3]);
    meshTail.addVertex(bodyTail[2]);
    meshTail.addVertex(bodyTail[21]);
    
    meshTail.addVertex(bodyTail[21]);
    meshTail.addVertex(bodyTail[20]);
    meshTail.addVertex(bodyTail[3]);
    
    meshTail.addVertex(bodyTail[22]);
    meshTail.addVertex(bodyTail[21]);
    meshTail.addVertex(bodyTail[5]);
    
    meshTail.addVertex(bodyTail[5]);
    meshTail.addVertex(bodyTail[13]);
    meshTail.addVertex(bodyTail[22]);
    
    meshTail.addVertex(bodyTail[23]);
    meshTail.addVertex(bodyTail[22]);
    meshTail.addVertex(bodyTail[10]);
    
    meshTail.addVertex(bodyTail[10]);
    meshTail.addVertex(bodyTail[11]);
    meshTail.addVertex(bodyTail[23]);
    
    meshTail.addVertex(bodyTail[6]);
    meshTail.addVertex(bodyTail[20]);
    meshTail.addVertex(bodyTail[23]);
    
    meshTail.addVertex(bodyTail[23]);
    meshTail.addVertex(bodyTail[14]);
    meshTail.addVertex(bodyTail[6]);
    
    
    // back tail end  side triangles clockwise
    meshTail.addVertex(bodyTail[21]);
    meshTail.addVertex(bodyTail[2]);
    meshTail.addVertex(bodyTail[5]);
    
    meshTail.addVertex(bodyTail[22]);
    meshTail.addVertex(bodyTail[13]);
    meshTail.addVertex(bodyTail[10]);
    
    meshTail.addVertex(bodyTail[14]);
    meshTail.addVertex(bodyTail[23]);
    meshTail.addVertex(bodyTail[11]);
    
    meshTail.addVertex(bodyTail[6]);
    meshTail.addVertex(bodyTail[3]);
    meshTail.addVertex(bodyTail[20]);
    
    
    //close tail end triangle
    meshTail.addVertex(bodyTail[20]);
    meshTail.addVertex(bodyTail[21]);
    meshTail.addVertex(bodyTail[22]);
    
    meshTail.addVertex(bodyTail[22]);
    meshTail.addVertex(bodyTail[23]);
    meshTail.addVertex(bodyTail[20]);
    
    
    
    setNormals(&meshTail);
    setColors(&meshTail);
    
    
}

void hexapod::scaleMesh(float scale_) {
    
    for (int i = 0; i < bodyHead.size(); i++) {
        bodyHead[i]*=scale_;
    }
    
    for (int i = 0; i < bodyCenter.size(); i++) {
        bodyCenter[i]*=scale_;
    }
    
    for (int i = 0; i < bodyTail.size(); i++) {
        bodyTail[i]*=scale_;
    }
    
    scale = scale_;
    lenTotal*= scale;
    mass = scale ;
    
}

void hexapod::setNormals(ofMesh* mesh_) {
    
    mesh_->clearNormals();
    
    for (int i = 1; i< mesh_->getNumVertices(); i+=3) {
        
        ofVec3f temp = mesh_->getVertex(i);
        ofVec3f tempA = temp - mesh_->getVertex(i-1) ;
        ofVec3f tempB = temp - mesh_->getVertex(i+1);
        
        temp = tempA.getCrossed(tempB);
        
        temp.normalize();
        
        mesh_->addNormal(temp);
        mesh_->addNormal(temp);
        mesh_->addNormal(temp);
        
        
    }
    
}

void hexapod::setColors(ofMesh* mesh_) {
    
    for (int i = 0; i < mesh_->getNumVertices(); i+=3) {
        
        mesh_->addColor( farbe) ;
        mesh_->addColor( farbe) ;
        mesh_->addColor( farbe) ;
    }
    
}



void hexapod::draw() {
    
    
    //    ofMesh PT;
    //    PT.setMode(OF_PRIMITIVE_LINE_STRIP);
    //    for (int i = 0; i < pathVertices.size(); i++) {
    //
    //       // ofVec3f temp
    //        PT.addVertex(pathVertices[i]);
    //        PT.addColor(ofColor::fromHsb(farbe.getHex(), 255, 255));
    //    }
    //
    //    PT.drawFaces();
    
    meshBody.setMode(OF_PRIMITIVE_TRIANGLES);
    meshBody.enableColors();
    meshBody.enableNormals();
    
    
    meshHead.setMode(OF_PRIMITIVE_TRIANGLES);
    meshHead.enableColors();
    meshHead.enableNormals();
    meshTail.setMode(OF_PRIMITIVE_TRIANGLES);
    meshTail.enableColors();
    meshTail.enableNormals();
    
    meshHead.drawFaces();
    meshBody.drawFaces();
    meshTail.drawFaces();
    
    
    //    meshHead.drawWireframe();
    //    meshBody.drawWireframe();
    //    meshTail.drawWireframe();
    
    trail.drawFaces();
    
}

void hexapod::drawNormals() {
    
    ofPushMatrix();
    
    ofTranslate(transPoint.x, transPoint.y, transPoint.z);
    ofRotateX(rotP.x);
    ofRotateY(rotP.y);
    ofRotateZ(rotP.z);
    
    
    for (int i=0; i < meshBody.getNumVertices(); i++) {
        
        ofVec3f aa = meshBody.getVertex(i);
        ofVec3f bb = meshBody.getNormal(i)*4;
        
        ofLine(aa.x, aa.y, aa.z, aa.x+bb.x, aa.y+bb.y, aa.z+bb.z);
    }
    
    for (int i=0; i < meshHead.getNumVertices(); i++) {
        
        ofVec3f aa = meshHead.getVertex(i);
        ofVec3f bb = meshHead.getNormal(i)*4;
        
        ofLine(aa.x, aa.y, aa.z, aa.x+bb.x, aa.y+bb.y, aa.z+bb.z);
    }
    
    for (int i=0; i < meshTail.getNumVertices(); i++) {
        
        ofVec3f aa = meshTail.getVertex(i);
        ofVec3f bb = meshTail.getNormal(i)*4;
        
        ofLine(aa.x, aa.y, aa.z, aa.x+bb.x, aa.y+bb.y, aa.z+bb.z);
    }
    
    ofPopMatrix();
}

void hexapod::rotateToNormal(ofVec3f normal_) {
    
    
    float rotAm;
    ofVec3f rotAngle;
    ofQuaternion rotation;
    ofVec3f axis(0,0,-1);
    rotation.makeRotate(axis, normal_);
    rotation.getRotate(rotAm, rotAngle);
    
    ofRotate(rotAm, rotAngle.x, rotAngle.y, rotAngle.z);
    
}



void hexapod::slowDown() {
    
    float tempsq =  vel.lengthSquared();
    
    if (tempsq > 950) {
        
        vel.normalize();
        vel*=22;
    }
    vel*= *velSlow;
    
}



