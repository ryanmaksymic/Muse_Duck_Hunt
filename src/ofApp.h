#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 5002
#define NUM_MSG_STRINGS 50

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void gunshot();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
};
