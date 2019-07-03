#include <CapacitiveSensor.h>
#include <NewPing.h>
/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */
#define TRIGGER_PIN 11 
#define ECHO_PIN 10
#define MAX_DISTANCE 500

//int for reading the distance in cm into.
int dist;

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);    

void setup()                    
{

  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

}

void loop()                    
{
   //  setting ping distance in cm to dist variable 
  dist = sonar.ping_cm();
  int total1 =  cs_4_2.capacitiveSensor(30);

  delay(100);
  
                      
 Serial.print(dist);  
 Serial.print(" ");
 Serial.println(total1);
 // Serial.print("/n");
   

   
}
