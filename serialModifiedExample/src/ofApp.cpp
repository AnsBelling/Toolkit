/*
	What the file should do: read serial data from two input devices from the Arduino and then assign these into two different variables

	Bug: I am only getting 0's when I try to 'cout' the sensor value variable.
	Individually the readByte() works.
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	//ofBackground(0, 0, 0);
	ofSetLogLevel(OF_LOG_VERBOSE);

	font.load("monospace", 24);

	iFeelYou.load("iFeelYou.mp3");
	iSeeYou.load("iSeeYou.mp3");
	iFeelYou.setVolume(0.75f);
	iFeelYou.setMultiPlay(true);
	iSeeYou.setVolume(0.75f);
	iSeeYou.setMultiPlay(true);

	startTime = ofGetElapsedTimeMillis();


	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	//serial2.listDevices();
	//vector <ofSerialDeviceInfo> deviceList2 = serial2.getDeviceList();


	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;

	//int baud2 = 115700;
	//serial.setup(0, baud); //open the first device
	serial.setup("COM3", baud); // windows example
	//serial2.setup("COM4", baud2);
	//serial.setup("tty.usbserial-A9007QuL", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSoundUpdate();
	//////SERIAL COMMUNICATION/////////////////////////////////////////////////////////////////////////////////////////////////////////7
	// Simple if statement to inform user if Arduino is sending serial messages.
	if (serial.available() < 0) {
		sensorValue = "Arduino Error";
	}
	else {
		// While statement looping through serial messages when serial is being provided.
		while (serial.available() > 0) {
			// byte data is being writen into byteData as int.
			byteData = serial.readByte();

			// cout << byteData << endl;  // This prints the values correctly with ASCII '32' in between values which is the space delimiter

			if (byteData == OF_SERIAL_NO_DATA || byteData == OF_SERIAL_ERROR || byteData == 0) break;

			// checks whether a new line symbol (\n) was received from Arduino.
			if (byteData == '\n') {
				// now splitting the received string str using the ofSplitString() function 
				// and use the resulting array of strings list to set values to two sensor variables
				vector<string> list = ofSplitString(str, " ");
				if (list.size() >= 2) {
					pingSensorValue = ofToFloat(list[0]);
					capSenseSensorValue = ofToInt(list[1]);
				}

				str = "";
			}
			else str.push_back(byteData);
		}
		//cout << capSenseSensorValue << endl;
		//cout << pingSensorValue << endl;

		//////STATES//////////////////////////////////////////////////////////////////////////////////////////////
		
		if (pingSensorValue<=200) {
			iSeeYouFunc();
		}
		if (capSenseSensorValue >= 80) iFeelYouFunc();

		
	


	}
}
//--------------------------------------------------------------
void ofApp::draw() {
	// ofSetColor(0);
	// msg = "press key a, b or c to test serial:\n";
    //  font.drawString(msg, 50, 60);
    // font.drawString("sensorValue: " + sensorValue, 50, 100);
}
void ofApp::ambientMood() {

	float time = ofGetElapsedTimef(); //Get time in seconds
	//Get periodic value in [-1,1], with wavelength equal to 1 second
	float value = sin(time * M_TWO_PI / 4);
	//Map value from [-1,1] to [0,255]
	float v = ofMap(value, -1, 1, 0, 255);
	ofBackground(0, v, 0);
}

void ofApp::iFeelYouFunc()
{
	cout << capSenseSensorValue << endl;
	if (capSenseSensorValue >=80) {
		float timer2 = ofGetElapsedTimeMillis();
		if (iFeelYou.isPlaying()==false && iSeeYou.isPlaying() == false) iFeelYou.play();

		if (timer2 >= 1500) {
			float currentTime2 = ofGetElapsedTimeMillis();
			iFeelYou.stop();

			// cout << currentTime2 << endl;
			if (currentTime2 >= 8000) {
				ofResetElapsedTimeCounter();
				float timer2 = ofGetElapsedTimeMillis();
			}
		}
		//if (capSenseSensorValue < 40) break;

	}
}

void ofApp::iSeeYouFunc()
{
	if (pingSensorValue <= 200 && pingSensorValue >= 50) {
		float timer = ofGetElapsedTimeMillis();
		if (iSeeYou.isPlaying()==false && iFeelYou.isPlaying()==false)	iSeeYou.play();

		if (timer >= 2000) {
			float currentTime = ofGetElapsedTimeMillis();
			iSeeYou.stop();

			// cout << currentTime << endl;
			if (currentTime >= 5000) {
				ofResetElapsedTimeCounter();
				float timer = ofGetElapsedTimeMillis();
			}
		}
		//if (pingSensorValue >= 201) break;
	}



}

