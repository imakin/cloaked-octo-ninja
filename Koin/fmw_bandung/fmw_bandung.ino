#include "Hx711.h"
//~ #include "OutputManager.h"
//~ #include "Stack.h"
#define k1 41
#define k2 52
#define k3 105

#define expectedW (k3*2 + k2 + k1*2)
#define TOLERANSI 15
#define RELAYPIN A3
static float Weight=0;
static float selisih = 0;

Hx711 scale(A0,A1);//-- param: A0-data 	A1-sck
//~ Outputs output;
String inputString = "";
boolean stringComplete = false;

void setup()
{
    //~ Serial.begin(9600);
    //~ delay(2000);
    //~ Serial.println("1");
    //~ delay(2000);
    //~ Serial.println("2");
    //~ delay(2000);
    //~ Serial.println("3");
    //~ delay(2000);
    while (1);
    //~ output.add(13);
    //~ output.add(RELAYPIN);
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
          //~ output.setAll();
          delay(500);
        }
        //~ else
        //~ {
            //~ output.clearAll();
        //~ }
    }
    //~ else
    //~ {
        //~ output.clearAll();
	//~ }
    delay(200);
}
