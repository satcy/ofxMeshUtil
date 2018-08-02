//
//  MeshUtil.h
//  Entrance
//
//  Created by satcy on 2017/02/17.
//
//

#pragma once
#include "ofMesh.h"

namespace MeshUtil {
    void minmax(const ofMesh & m, ofVec3f & min_, ofVec3f & max_);
    
    float getVoxelVolume(const ofMesh & m);
    
    float getVoxelVolume(const ofMesh & m, ofVec3f & in_size);
    
    ofVec3f getMiddle(const ofMesh & m);
    
    float getSignedVolumeOfTriangle(const ofVec3f & p1, const ofVec3f & p2, const ofVec3f & p3);
    
    float getVolumeOfMesh(const ofMesh & mesh);
    
    ofVec3f getPointOnTriangle(const ofVec3f & a,
                               const ofVec3f & b,
                               const ofVec3f & c,
                               float x, float y);
    
    bool getIsPointOnTriangle(const ofVec3f & a,
                             const ofVec3f & b,
                             const ofVec3f & c,
                             const ofVec3f & p,
                              float strict = 1.0);
    
    void calculateNormal(ofMeshFace & f);
    
    void calcurateNormal(ofMeshFace & f);
    
    void calculateNormals(ofMesh& mesh, bool bNormalize = true);
}
