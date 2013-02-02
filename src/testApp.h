#pragma once

#include "ofMain.h"
#include "ofxControlPanel.h"
#include "ofxXmlSettings.h"

#define NUM_SENSORS 4
#define NUM_NODES 144
#define NUM_ROWS 12
#define NUM_COLS 12

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void gotMessage(ofMessage msg);
    
    
    // GENERAL SERIAL STUFF
    ofSerial	serialA;
    ofSerial	serialB;
    ofSerial*   FloorSerial;
    ofSerial*   CloudSerial;
    
    bool        aIsSetup;
    bool        bIsSetup;
    bool        bFlushA;
    bool        bFlushB;
    
    // CONTROL SETTINGS AND VARS
    ofxControlPanel panel;
    
    float   power;
    float   threshold;
    bool    building;
    bool    release;
    
    int     minAmp;
    int     maxAmp;
    float   buildSpeed;
    float   releaseSpeed;
    int     changeSpeed;
    float   sensitivity;
    
    
    // CEILING DATA
    bool        sendByte;
    int         bytesOut[3];
    int         active;
    int         activeRow;
    int         activeCol;
    ofPoint     n[NUM_ROWS * NUM_COLS];
    
    
    // FLOOR DATA AND CONVERSIONS
    bool            receiveByte;
    bool            recieveComplete;
    unsigned char   bytesReturned[NUM_SENSORS];    
    int             sensorReadings[NUM_SENSORS];
    float           smoothedReadings[NUM_SENSORS];
    ofPoint         sensors[NUM_SENSORS];
    
    // DEBUG STUFF
    bool        fullSequence;
    float       maxSensor;
    
    
    bool bActivate;
    
};
