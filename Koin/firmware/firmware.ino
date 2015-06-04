#include "Hx711.h"
#define k1 38
#define k2 51
#define k3 101
/*
1,5,10 ->27 =
-----
10 10 5 1 1 = k3*2 + k2 + k1*2
10 5 5 1 1
5 5 5 5 1 1
*/
#define expectedW (k3*2+k2+k1*2) // or k3+k2*3+k1*2 or k2*5+k1*2
#define RELAYPIN A3
namespace Relay{
	void Off()
	{
		digitalWrite(RELAYPIN,HIGH);
	}
	void On()
	{
		digitalWrite(RELAYPIN,LOW);
	}
};
static float Weight=0;
static float selisih = 0;
Hx711 scale(A0,A1);
void setup()
{
    Serial.begin(9600);
    pinMode(A3, OUTPUT);
    Relay::Off();
    delay(200);
    Relay::On();
}

void loop()
{
    Weight = scale.getGram();
    selisih = Weight - expectedW;
    if (selisih<9 && selisih>-9)
    {
        Relay::On();
        delay(500);
    }
    else
        Relay::Off();
    
    delay(200);
}
