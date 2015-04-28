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
#define expectedW (k3*2 + k2 + k1*2)
static float Weight=0;
static float selisih = 0;
Hx711 scale(A0,A1);
void setup()
{
    Serial.begin(9600);
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
    if (selisih<9 && selisih>-9)
    {
        Serial.println(" Succeed");
        delay(500);
    }
    delay(200);
}
