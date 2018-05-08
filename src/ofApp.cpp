#include "ofApp.h"

int c_root = 4;
int c_cube = c_root*c_root*c_root;
int box_span = 40;

class Boxes{
public:
    vector<box> box_arr;
    
    Boxes(int num){
        box_arr.resize(num);
    }
    
    void setPos(int num, ofVec3f pos){
        box_arr[num].setPos(pos);
    }
    
    void setColor(int num, ofColor color){
         box_arr[num].setColor(color);
    }
    
    void update(){
        for(int i = 0; i < box_arr.size(); i++)
            box_arr[i].update();
    }
    
    void draw(){
        for(int i = 0; i < box_arr.size(); i++)
            box_arr[i].draw();
        
    }
    
    void moveBox(){
        for(int i = 0; i < box_arr.size(); i++)
            box_arr[i].move();
    }
    
    
};

vector<Boxes> cube;

class TriPos{
public:
    ofVec3f boxesNum;
    ofVec3f boxNum;
    
    TriPos(ofVec3f bsNum, ofVec3f bNum){
        boxesNum = bsNum;
         boxNum = bNum;
    }
    
    void setBoxesNum(ofVec3f Num){
        boxesNum = Num;
    }
    
    void setBoxNum(ofVec3f Num){
        boxNum = Num;
    }
    
    void draw(){
        box a,b,c;
        a = cube[boxesNum.x].box_arr[boxNum.x];
        b = cube[boxesNum.y].box_arr[boxNum.y];
        c = cube[boxesNum.z].box_arr[boxNum.z];

        ofSetColor(240,240,240,30);
        glBegin(GL_TRIANGLES);
        glVertex3f(a.pos.x,a.pos.y,a.pos.z);
        glVertex3f(b.pos.x,b.pos.y,b.pos.z);
        glVertex3f(c.pos.x,c.pos.y,c.pos.z);
        glEnd();
    }
    
};

vector<TriPos> Triangles;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
    //cam.setPosition(-100,100,100);
    
    for(int i = 0; i < 8; i++)
        cube.push_back(Boxes(c_root*c_root*c_root));
    
    int num;
    for(int n = 0; n < cube.size(); n++){
        num = 0;
        for(int i = 0; i < c_root; i++)
            for(int j = 0; j < c_root; j++)
                for(int k = 0; k < c_root; k++){
                    ofVec3f pos;
                    switch(n){
                        case 0:
                            pos.set(i*box_span,j*box_span,k*box_span);
                            break;
                        case 1:
                            pos.set(i*box_span,j*box_span,-k*box_span);
                            break;
                        case 2:
                            pos.set(i*box_span,-j*box_span,k*box_span);
                            break;
                        case 3:
                            pos.set(i*box_span,-j*box_span,-k*box_span);
                            break;
                        case 4:
                            pos.set(-i*box_span,j*box_span,k*box_span);
                            break;
                        case 5:
                            pos.set(-i*box_span,j*box_span,-k*box_span);
                            break;
                        case 6:
                            pos.set(-i*box_span,-j*box_span,k*box_span);
                            break;
                        case 7:
                            pos.set(-i*box_span,-j*box_span,-k*box_span);
                            break;
                    }
                    cube[n].setPos(num,pos);
                    num++;
                }
    }
    
    buffSize = c_root*c_root*c_root;
    //sound.loadSound("Perfume_globalsite_sound.wav");
    sound.loadSound("01 If you wanna.mp3");
    sound.play();
    
    nBands = c_root*c_root*c_root;
    fft.assign(nBands, 0.0);
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    float * val = ofSoundGetSpectrum(nBands);
    vector<float> currentFft;
    for (int i = 0; i < nBands; i++) {
        fft[i]  = val[i];
    }
    
    for(int i = 0; i < cube.size(); i++)
        cube[i].update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    float specSum = 0;
    for(int i = 0; i < fft.size(); i++){
        specSum += fft[i];
    }
    
    if(specSum >= 20.0){
        cout << "spec " << specSum << endl;
        for(int i = 0; i < cube.size(); i++)
            cube[i].moveBox();
    }
    
    if(specSum >= 15.0){
        Triangles.clear();
        for(int i = 0; i < 20; i++){
            ofVec3f bsNum = ofVec3f((int)ofRandom(0,8),(int)ofRandom(0,8),(int)ofRandom(0,8));
            ofVec3f bNum = ofVec3f((int)ofRandom(0,c_cube),(int)ofRandom(0,c_cube),(int)ofRandom(0,c_cube));
            TriPos tri(bsNum,bNum);
            Triangles.push_back(tri);
        }
    }

    
    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < fft.size(); j++){
            ofColor col;
            float hue = ofMap(j, 0, fft.size(), 80, 180);
            float br = ofMap(fft[j], 0, 1, 30, 255);
            col.setHsb(hue,255,br);
            
            
            cube[i].setColor(j,col);
        }
        
        cube[i].draw();
    }
    
    //何かの値をトリガーにして、ランダムにboxを3つ選んでそれを繋いだ三角形描画
    //本にあったフレームをトリガーにするやつみたいなの
    //static int step = ofRandom(10,100);
    //if(ofGetFrameNum() % step == 0){
        //step = ofRandom(10,100);
    //}
    
    for(int i = 0; i < Triangles.size(); i++){
        Triangles[i].draw();
    }

    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
