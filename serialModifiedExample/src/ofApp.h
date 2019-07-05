#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
	///////METHODS////////////////////////////////////////////////////////
    void setup();
    void update();
    void draw();

	void ambientMood();
   
	void iFeelYouFunc();
	void iSeeYouFunc();



	//////VARIABLES//////////////////////////////////////////////////
    ofTrueTypeFont		font;
     
	string str;
    ofSerial	serial;
	
	ofSoundPlayer iFeelYou;
	ofSoundPlayer iSeeYou;

    string sensorValue;
    int byteData;
	int pingSensorValue;
	unsigned int capSenseSensorValue;
    string msg;
};

