/*
	What the file should do: read serial data from two input devices from the Arduino and then assign these into two different variables

	Bug: I am only getting 0's when I try to 'cout' the sensor value variable.
	Individually the readByte() works.
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);

	font.load("monospace", 24);

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	//serial.setup(0, baud); //open the first device
	serial.setup("COM3", baud); // windows example
	//serial.setup("tty.usbserial-A9007QuL", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
}

//--------------------------------------------------------------
void ofApp::update() {

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
			if (byteData == '/n') {
				// now splitting the received string str using the ofSplitString() function 
				// and use the resulting array of strings list to set values to two sensor variables
				vector<string> list = ofSplitString(str, " "); // splits the string str to its parts using space as a delimiter
				if (list.size() > 2) { // checks that there are at least two strings in the resulted array list
					pingSensorValue = ofToFloat(list[0]); // convert strings of list to int values and set them to the sensor variables
					capSenseSensorValue = ofToFloat(list[1]);

					//cout << ofToString(list[0]); 
				}
				str = "";


				//cout << ofToString(list[0]);
			}
			else str.push_back(byteData);

		    // cout << capSenseSensorValue << endl; // output: currently 0's

			//cout << pingSensorValue<< endl; // output: currently only 0's

			//byteData is converted into a string for drawing later.
			//sensorValue = "value: " + ofToString(byteData);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// ofSetColor(0);
	// msg = "press key a, b or c to test serial:\n";
    //  font.drawString(msg, 50, 60);
    // font.drawString("sensorValue: " + sensorValue, 50, 100);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

