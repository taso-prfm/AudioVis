//
//  box.cpp
//  mySketch
//
//  Created by Taka on 2018/02/11.
//
//

#include "box.h"

box::box(){
    pos.set(0,0,0);
    vel.set(0,0,0);
    force.set(0,0,0);
    color.set(255,255,255);
}

void box::setup(){
}

void box::update(){
    //pos += vel;
    if(vel.x != 0){
        pos.x += vel.x;
        if(vel.x > 0)
            vel.x -= 1;
        else
            vel.x += 1;
    }
    if(vel.y != 0){
        pos.y += vel.y;
        if(vel.y > 0)
            vel.y -= 1;
        else
            vel.y += 1;
    }
    if(vel.z != 0){
        pos.z += vel.z;
        if(vel.z > 0)
            vel.z -= 1;
        else
            vel.z += 1;
    }
}

void box::draw(){
    
    ofSetColor(color);
    b.set(10);
    b.setPosition(pos);
    b.drawWireframe();
}

void box::setPos(ofVec3f pos){
    this->pos = pos;
}

ofVec3f box::getPos(){
    return pos;
}

void box::setVel(ofVec3f vel){
    this->vel = vel;
}

ofVec3f box::getVel(){
    return vel;
}
void box::setForce(ofVec3f force){
    this->force = force;
}

ofVec3f box::getForce(){
    return force;
}

void box::setColor(ofColor color){
    this->color = color;
}

void box::move(){
    int vec = (int)ofRandom(0,3);
    int length = (int)ofRandom(-20,20);
    
    /*
    switch(vec){
        case 0:
            pos.x += length;
            break;
        case 1:
            pos.y += length;
            break;
        case 2:
            pos.z += length;
            break;
        default:
            break;
    }
     */
    //pos += ofVec3f((int)ofRandom(-10,10),(int)ofRandom(-10,10),(int)ofRandom(-10,10));
    vel = ofVec3f((int)ofRandom(-5,5),(int)ofRandom(-5,5),(int)ofRandom(-5,5));

}

