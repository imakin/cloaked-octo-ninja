#include "Hx711.h"
#include "OutputManager.h"
#include "Stack.h"
#define k1 41
#define k2 52
#define k3 105

#define expectedW (k3*2 + k2 + k1*2)
#define TOLERANSI 15
#define RELAYPIN A3
static float Weight=0;
static float selisih = 0;

Hx711 scale(A0,A1);//-- param: A0-data 	A1-sck
Outputs output;
String inputString = "";
boolean stringComplete = false;

void setup()
{
    Serial.begin(9600);
    output.add(13);
    output.add(RELAYPIN);
    for (uint8_t i=0;i<=20;i++)
	{
		output.add(i);
	}
    delay(1000);
    while(1)
    {
		
	}
}

void loop()
{
    Weight = scale.getGram();
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
        Weight = scale.getGram();
        selisih = Weight - expectedW;
        if (selisih<TOLERANSI && selisih>-TOLERANSI)
        {
          Serial.println(" Succeed");
          //~ Relay::on();
          delay(500);
        }
        else
        {
            //~ Relay::off();
        }
    }
    else
        //~ Relay::off();
    delay(200);
}
