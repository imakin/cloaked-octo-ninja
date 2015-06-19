#include "Stack.h"
#include "OutputManager.h"
#define LED 13
void LedOn() { digitalWrite(LED,HIGH); }
void LedOff() { digitalWrite(LED,LOW); }

struct DPin{
	uint8_t input;
	uint8_t grounder;
};
class Magnet{
	public:
		DPin Dev;
		Magnet(const uint8_t a,const uint8_t b) { 
			Dev.input = a;
			Dev.grounder = b;
			pinMode(Dev.input,INPUT);
			pinMode(Dev.grounder,OUTPUT);
			digitalWrite(Dev.input,HIGH);
			digitalWrite(Dev.grounder,LOW);
		};
		bool IsShorted();
		~Magnet() {};
};
bool Magnet::IsShorted() {
	if (digitalRead(Dev.input)==LOW)
		return true;
	return false;
}

Magnet *m1 = new Magnet(A2,A3);
Magnet *m2 = new Magnet(A4,A5);
Outputs output;
void setup() {
	Serial.begin(9600);
	delay(1000);
	pinMode(LED,OUTPUT);
	output.add(LED);
	output.add(12);
	output.add(11);
	output.add(10);
	Serial.println("here");
}
void loop() {
	Serial.println("step");
	if (m1->IsShorted())
		Serial.println("m1 shorted");
	if (m2->IsShorted())
		Serial.println("m2 shorted");

	if (m1->IsShorted() && m2->IsShorted())
		output.setAll();
	else
		output.clearAll();
	delay(500);
}
