#include "Hx711.h"
#include "OutputManager.h"
#define k1 41
#define k2 52
#define k3 105

#define expectedW (k3*2 + k2 + k1*2)
#define TOLERANSI 15
#define RELAYPIN A2
static float Weight=0;
static float selisih = 0;

Hx711 *scale;//(A0,A1);//-- param: A0-data 	A1-sck
Outputs output;

void RelayTes(Outputs *o)
{
	o->clearAll();
	delay(1000);
	o->setAll();
}
void RelayON(Outputs *o)
{
	o->clearAll();
}
void RelayOFF(Outputs *o)
{
	o->setAll();
}

void setup()
{
	Serial.begin(9600);
	delay(1000);
	//~ while(!Serial);
	scale = new Hx711(A0,A1);
	output.add(A2);
	output.add(A3);
	RelayTes(&output);
}

void loop()
{
    Weight = scale->getGram();
    selisih = Weight - expectedW;
    Serial.print(Weight,1);
    Serial.print(" ");
    Serial.print(selisih,1);
    Serial.print(" ");
    Serial.print(expectedW,1);
    
    Serial.println(" g");
    if (selisih<TOLERANSI && selisih>-TOLERANSI)
    {
        delay(1000);
        Weight = scale->getGram();
        selisih = Weight - expectedW;
        if (selisih<TOLERANSI && selisih>-TOLERANSI)
        {
          Serial.println(" Succeed");
          RelayON(&output);
          delay(500);
        }
        else
        {
			RelayOFF(&output);
        }
    }
    else
    {
		RelayOFF(&output);
	}
    delay(200);
}
