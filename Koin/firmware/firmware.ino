#include "Hx711.h"
#define k1 41
#define k2 52
#define k3 105/*
#define k1 32
#define k2 40
#define k3 80*/
/*
1,5,10 ->27 =
-----
10 10 5 1 1 = k3*2 + k2 + k1*2
10 5 5 1 1
5 5 5 5 1 1
*/
#define expectedW (k3*2 + k2 + k1*2 -10)
#define TOLERANSI 26
static float Weight=0;
static float selisih = 0;
Hx711 scale(A0,A1);

#define RELAYPIN A3

namespace Relay{
    void init();
    void on();
    void off();
};

void Relay::init(){
    pinMode(RELAYPIN,OUTPUT);
    Relay::on();
    delay(200);
    Relay::off();
}

void Relay::on()
{
    digitalWrite(RELAYPIN,LOW);
}
void Relay::off()
{
    digitalWrite(RELAYPIN,HIGH);
}

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.write("bismillah");
    Relay::init();
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
          Relay::on();
          delay(500);
        }
        else
        {
            Relay::off();
        }
    }
    else
        Relay::off();
    delay(200);
}
