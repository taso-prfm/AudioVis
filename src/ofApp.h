#pragma once

#include "ofMain.h"
#include "box.h"
#include "ofxEasyFft.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
        ofEasyCam cam;
        ofLight light;
    
        //ofxPanel gui;

        //ofxEasyFft fft;
    
        ofSoundPlayer sound;
        int buffSize;
    
        vector<float> fft;
        int nBands;
};

