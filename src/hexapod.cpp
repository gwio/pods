

#include "hexapod.h"

//________________________________________________
hexapod::hexapod() {
    
    
    //translate Position
    transP = ofVec3f(0,0,0);
    transPoint.set(transP);
    ///central POSITION
    bodyCenterPos = ofVec3f(0,0,0);
   //rotation
    rotP = ofVec3f(0,0,0);
    
    //______________________________________________________________________________ //body
    bodyToHeadDia = 3;
    bodyToHeadDist = 12;
    
    bodyToTailDia = 2.5;
    bodyToTailDist = 6;
    
    bodyFrontW = 22;
    bodyFrontH = 22;
    
    bodyBackW = 12;
    bodyBackH = 22;
    
    bodyLen = 30;
    
    
    //_______________________________________________________________________________ //head
    headFrontW = 12;
    headFrontH = 12;
    
    headBackW = 12;
    headBackH = 22;
    
    headLen = 12;
    
    headOffset = (bodyLen/2) +(bodyToHeadDist) + (headLen/2);
    
    
    //_______________________________________________________________________ //tail
    tailFrontW = 7;
    tailFrontH = 7;
    
    tailBackW = 11.5;
    tailBackH = 11.5;
    
    tailLen = 18;
    
    tailOffset = (bodyLen/2) +(bodyToTailDist) + (tailLen/2);
    
    //------------ total length
    lenTotal = headLen+bodyLen+tailLen+bodyToHeadDist+bodyToTailDist;
    
    
    //defualt x and y deformation
    radiusYScale = 0.0;
    radiusXScale = 0.0;
    
    initMeshPoints();
    updateMesh();
    
}

void hexapod::update() {
    
    
}

void hexapod::initMeshPoints() {
    
    
    
    bodyHead.clear();
    bodyCenter.clear();
    bodyTail.clear();
    
    
    headOffset = (bodyLen/2) +(bodyToHeadDist) + (headLen/2);
    tailOffset = (bodyLen/2) +(bodyToTailDist) + (tailLen/2);
    lenTotal = headLen+bodyLen+tailLen+bodyToHeadDist+bodyToTailDist;
    
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
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), -headOffset + bodyCenterPos.z - (bodyToHeadDist/2) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y + (bodyToHeadDia/2), -headOffset + bodyCenterPos.z - (bodyToHeadDist/2) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x + (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), -headOffset + bodyCenterPos.z - (bodyToHeadDist/2) - (headLen/2) ) );
    bodyHead.push_back( ofVec3f( bodyCenterPos.x - (bodyToHeadDia/2), bodyCenterPos.y - (bodyToHeadDia/2), -headOffset + bodyCenterPos.z - (bodyToHeadDist/2) - (headLen/2) ) );
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
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), tailOffset + bodyCenterPos.z + (bodyToTailDist/2) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y + (bodyToTailDia/2), tailOffset + bodyCenterPos.z + (bodyToTailDist/2) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x + (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), tailOffset + bodyCenterPos.z + (bodyToTailDist/2) + (tailLen/2) ) );
    bodyTail.push_back( ofVec3f( bodyCenterPos.x - (bodyToTailDia/2), bodyCenterPos.y - (bodyToTailDia/2), tailOffset + bodyCenterPos.z + (bodyToTailDist/2) + (tailLen/2) ) );
    
    // add x,z and y,z deformation
    updateMeshRadiusX(&bodyHead, &bodyCenter, &bodyTail);
    updateMeshRadiusY(&bodyHead, &bodyCenter, &bodyTail);
    
    
    updateMesh();
    
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
        float temp = ofRandom(255);
        mesh_->addColor( ofColor::fromHsb( temp, 170, 215, 255)) ;
          mesh_->addColor( ofColor::fromHsb( temp, 170, 215, 255)) ;
          mesh_->addColor( ofColor::fromHsb( temp, 170, 215, 255)) ;
    }
    
}

void hexapod::updateMeshRadiusY( vector<ofVec3f>* bodyHead_, vector<ofVec3f>* bodyCenter_, vector<ofVec3f>* bodyTail_) {
    
    for (int i = 0; i < bodyHead_->size(); i++) {
        ofVec3f in = bodyHead_->at(i);
        float theta =  in.x/ in.length();
        //   float thetha2 = in.length();
        in.x = -sin(theta+radiusYScale)*in.z;
        in.z = cos(theta+radiusYScale)*in.z;
        bodyHead_->at(i).x = in.x;
        bodyHead_->at(i).y = in.y;
        bodyHead_->at(i).z = in.z;
    }
    
    for (int i = 0; i < bodyCenter_->size(); i++) {
        if (  abs(bodyCenter_->at(i).z) > (bodyLen/2)) {
            ofVec3f in = bodyCenter_->at(i);
            if (in.z < 0) {
                float theta =  in.x/ in.length();
                //   float thetha2 = in.length();
                in.x = -sin(theta+radiusYScale)*in.z;
                in.z = cos(theta+radiusYScale)*in.z;
            } else {
                float theta =  in.x/ in.length();
                //   float thetha2 = in.length();
                in.x = sin(theta+radiusYScale)*in.z;
                in.z = cos(theta+radiusYScale)*abs(in.z);
            }
            bodyCenter_->at(i).x = in.x;
            bodyCenter_->at(i).y = in.y;
            bodyCenter_->at(i).z = in.z;
        }
    }
    
    for (int i = 0; i < bodyTail_->size(); i++) {
        ofVec3f in = bodyTail_->at(i);
        float theta =  in.x/ in.length();
        //   float thetha2 = in.length();
        in.x = sin(theta+radiusYScale)*in.z;
        in.z = cos(theta+radiusYScale)*abs(in.z);
        bodyTail_->at(i).x = in.x;
        bodyTail_->at(i).y = in.y;
        bodyTail_->at(i).z = in.z;
    }
}

void hexapod::updateMeshRadiusX(vector<ofVec3f>* bodyHead_, vector<ofVec3f>* bodyCenter_, vector<ofVec3f>* bodyTail_) {
    
    for (int i = 0; i < bodyHead_->size(); i++) {
        ofVec3f in = bodyHead_->at(i);
        
        float theta =  in.y/ in.length();
        
        //   float thetha2 = in.length();
        in.y = -sin(theta+radiusXScale)*in.z;
        in.z = cos(theta+radiusXScale)*in.z;
        
        bodyHead_->at(i).x = in.x;
        bodyHead_->at(i).y = in.y;
        bodyHead_->at(i).z = in.z;
    }
    
    for (int i = 0; i < bodyCenter_->size(); i++) {
        if (  abs(bodyCenter_->at(i).z) > (bodyLen/2)) {
            ofVec3f in = bodyCenter_->at(i);
            
            if (in.z < 0) {
                float theta =  in.y/ in.length();
                //   float thetha2 = in.length();
                
                in.y = -sin(theta+radiusXScale)*in.z;
                in.z = cos(theta+radiusXScale)*in.z;
            } else {
                float theta =  in.y/ in.length();
                //   float thetha2 = in.length();
                
                in.y = sin(theta+radiusXScale)*in.z;
                in.z = cos(theta+radiusXScale)*abs(in.z);
            }
            
            bodyCenter_->at(i).x = in.x;
            bodyCenter_->at(i).y = in.y;
            bodyCenter_->at(i).z = in.z;
        }
    }
    
    for (int i = 0; i < bodyTail_->size(); i++) {
        ofVec3f in = bodyTail_->at(i);
        
        float theta =  in.y/ in.length();
        
        //   float thetha2 = in.length();
        in.y = sin(theta+radiusXScale)*in.z;
        in.z = cos(theta+radiusXScale)*abs(in.z);
        
        bodyTail_->at(i).x = in.x;
        bodyTail_->at(i).y = in.y;
        bodyTail_->at(i).z = in.z;
    }
    
}



void hexapod::draw() {
    
    ofPushMatrix();
    
    ofTranslate(transPoint);
    ofRotateX(rotP.x);
    ofRotateY(rotP.y);
    ofRotateZ(rotP.z);
    
    
    
    meshBody.setMode(OF_PRIMITIVE_TRIANGLES);
    meshBody.enableColors();
    meshBody.enableNormals();
    meshHead.setMode(OF_PRIMITIVE_TRIANGLES);
    meshHead.enableColors();
    meshHead.enableNormals();
    meshTail.setMode(OF_PRIMITIVE_TRIANGLES);
    meshTail.enableColors();
    meshTail.enableNormals();
    
    
    
    meshBody.drawFaces();
    meshHead.drawFaces();
    meshTail.drawFaces();
    
    ofPopMatrix();
}

void hexapod::drawNormals() {
    
    ofPushMatrix();
    
    ofTranslate(transPoint);
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
    
//    
//    for (int i=0; i < wingsVertexUP.getNumVertices(); i++) {
//        
//        ofVec3f aa = wingsVertexUP.getVertex(i);
//        ofVec3f bb = wingsVertexUP.getNormal(i)*4;
//        
//        
//        ofLine(aa.x, aa.y, aa.z, aa.x+bb.x, aa.y+bb.y, aa.z+bb.z);
//    }
    ofPopMatrix();
}
