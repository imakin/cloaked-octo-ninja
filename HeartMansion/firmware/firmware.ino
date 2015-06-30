#include "Stack.h"
#include "OutputManager.h"
#define LED 13
#define Kunci() output.setAll()
#define Buka() output.clearAll()

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
		boolean IsShorted();
		~Magnet() {};
};
boolean Magnet::IsShorted() {
	if (digitalRead(Dev.input)==LOW)
		return true;
	return false;
}

Magnet *m1 = new Magnet(A2,A3);
Magnet *m2 = new Magnet(A4,A5);
unsigned long milis0;
unsigned long milis1;
Outputs output;
void setup() {
	milis0 = 0; //-- static one
	milis1 = 0; //-- updated one
	Serial.begin(9600);
	delay(1000);
	pinMode(LED,OUTPUT);
	output.add(LED);
	output.add(12);
	output.add(11);
	output.add(10);
	Serial.println("here");
	Kunci();
}
void loop() {
	Serial.println("step");
	boolean a,b;
	a = m1->IsShorted();
	b = m2->IsShorted();
	if (a)
		Serial.println("m1 shorted");
	if (b)
		Serial.println("m2 shorted");
	//Serial.println("BISMILLAH");
	if (a && b)
	{
		Serial.println("Harusnya masuk");
		Buka();
		uint8_t detik = 0;
		Serial.println("Harusnya masuk");
		while (m1->IsShorted() && m2->IsShorted())
		{
			delay(1000);
			Serial.println(detik);
			if (detik<16)
				detik += 1;
			if (detik>=15)
				Kunci();
  		}
	}
	else
		Kunci();
	delay(500);
}
