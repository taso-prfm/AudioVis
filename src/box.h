//
//  box.h
//  mySketch
//
//  Created by Taka on 2018/02/11.
//
//
#pragma once
#include "ofMain.h"

class box{
public:
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f force;
    ofColor color;
    
    
    box();
    void setup();
    void update();
    void draw();
    
    ofVec3f getPos();
    void setPos(ofVec3f pos);
    ofVec3f getVel();
    void setVel(ofVec3f vel);
    ofVec3f getForce();
    void setForce(ofVec3f force);
    
    void setColor(ofColor color);
    
    void move();
    
    ofBoxPrimitive b;
    
    
};
