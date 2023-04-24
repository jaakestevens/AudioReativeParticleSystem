#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class particle {
    
    public:
    float size; //size of circle
    int life;
    glm::vec2 force, position, direction; //vec2 for the particle
    float *shapefft; //shape of the fft
    float particleSpreadSpeed;
    
    
    void update(int gravityForceClass); //update includes a force of gravity that it is passed
    void draw(float frequency, float particleSpreadSpeed); //frequency value that affects the size
    
    particle(int x, int y); //starting values
    ~particle(); //destructor
};


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
        
    vector<particle> particles; //vector of particles that are added by drawing with the mouse
        
    
    ofxPanel gui; //graphical user interface
    
    //gui parameters
    ofParameter<float> volume;
    ofParameter<float> decay;
    ofParameter<bool> audioReactive;
    ofParameter<bool> gravity;
    ofParameter<int> gravityStrength;
    ofParameter<int> systemSize;
    ofParameter<float> spreadSpeed;
    
    //plays audio file
    ofSoundPlayer sound;
    
    //Arrays
    float *fft;
    float *soundSpectrum;
    
    //more bands means more control from frequency to manipulate visuals
    int bands;
    
    //hides gui
    bool hide;
    
    //force of gravity
    int gravityForce;
    
    //makes the frequency spectrum look nicer
    float relativeGain;
    
    //Amount of max particles
    int cutoffAmount;
		
};
