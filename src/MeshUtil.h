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
    void minmax(const ofMesh & m, ofVec3f & min_, ofVec3f & max_) {
        for ( auto & p : m.getVertices() ) {
            if ( p.x < min_.x ) min_.x = p.x;
            if ( p.x > max_.x ) max_.x = p.x;
            
            if ( p.y < min_.y ) min_.y = p.y;
            if ( p.y > max_.y ) max_.y = p.y;
            if ( p.z < min_.z ) min_.z = p.z;
            if ( p.z > max_.z ) max_.z = p.z;
        }
    }
    float getVoxelVolume(const ofMesh & m) {
        ofVec3f min_(999999999);
        ofVec3f max_(-999999999);
        minmax(m , min_, max_);
        return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
    }
    
    float getVoxelVolume(const ofMesh & m, ofVec3f & in_size) {
        ofVec3f min_(999999999);
        ofVec3f max_(-999999999);
        minmax(m ,min_, max_);
        in_size.x = (max_.x - min_.x);
        in_size.y = (max_.y - min_.y);
        in_size.z = (max_.z - min_.z);
        return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
    }
    
    ofVec3f getMiddle(const ofMesh & m) {
        ofVec3f min_(999999999);
        ofVec3f max_(-999999999);
        minmax(m ,min_, max_);
        return ofVec3f((max_.x + min_.x)*0.5, (max_.y + min_.y)*0.5, (max_.z + min_.z)*0.5);
    }
    
    float getSignedVolumeOfTriangle(const ofVec3f & p1, const ofVec3f & p2, const ofVec3f & p3)
    {
        return p1.dot(p2.getCrossed(p3)) / 6.0f;
    }
    
    float getVolumeOfMesh(const ofMesh & mesh) {
        const vector<ofMeshFace> & faces = mesh.getUniqueFaces();
        float vol = 0;
        for ( auto & f : faces ) {
            vol += getSignedVolumeOfTriangle(f.getVertex(0), f.getVertex(1), f.getVertex(2));
        }
        return vol;
    }
    
    ofVec3f getPointOnTriangle(const ofVec3f & a,
                               const ofVec3f & b,
                               const ofVec3f & c,
                               float x, float y) {
        ofVec3f p0, p1;
        ofVec3f mid = (a + b + c) / 3.0;
        float ratio = 0;
        if ( x < 1/3.0 ) {
            p0.set(a); p1.set(b);
            ratio = ofMap(x, 0, 1/3.0, 0, 1);
        } else if ( x < 2/3.0 ) {
            p0.set(b); p1.set(c);
            ratio = ofMap(x, 1/3.0, 2/3.0, 0, 1);
        } else {
            p0.set(c); p1.set(a);
            ratio = ofMap(x, 2/3.0, 1, 0, 1);
        }
        return mid.getInterpolated(p0, ratio).getInterpolated(mid.getInterpolated(p1, ratio), y);
    }
    
    bool geIsPointOnTriangle(const ofVec3f & a,
                             const ofVec3f & b,
                             const ofVec3f & c,
                             const ofVec3f & p,
                             float strict = 1.0) {
        double dot0, dot1, dot2;
        double accumilator = 0;
        
        ofVec3f line1, line2;
        line1 = a - p; line1.normalize();
        line2 = b - p; line2.normalize();
        dot0 = line1.dot(line2);
        
        line1 = b - p; line1.normalize();
        line2 = c - p; line2.normalize();
        dot1 = line1.dot(line2);
        
        line1 = c - p; line1.normalize();
        line2 = a - p; line2.normalize();
        dot2 = line1.dot(line2);
        
        accumilator = acos(dot0) + acos (dot1) + acos(dot2);
        if(accumilator < ofDegToRad(359.9 * strict))
            return false;
        else
            return true;
    }
    
    void calculateNormal(ofMeshFace & f) {
        ofVec3f U, V;
        
        U = (f.getVertex(1)-f.getVertex(0));
        V = (f.getVertex(2)-f.getVertex(0));
        
        ofVec3f n = U.getCrossed(V).getNormalized();
        
        f.setNormal(0, n);
        f.setNormal(1, n);
        f.setNormal(2, n);
    }
    
    void calcurateNormal(ofMeshFace & f) {
        calculateNormal(f);
    }
}
