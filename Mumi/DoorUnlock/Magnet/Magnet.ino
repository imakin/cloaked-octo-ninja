#define INPUTKUNCI 0
#define INPUTMEDALI 1
static const uint8_t LED[4]={5,6,10,9};
static const uint8_t LNUM = 4;
int LEDisON;

int i;
void LedOn()
{
    Serial.println("on");
    LEDisON = 1;
    int b;
    for(b=0;b<255;b++)
    {
        for(i=0;i<LNUM;i++)
        {
            analogWrite(LED[i],b);
        }
        delay(10);
    }
    digitalWrite(LED[0],HIGH);
    digitalWrite(LED[1],HIGH);
    digitalWrite(LED[2],HIGH);
    digitalWrite(LED[3],HIGH);
}
void LedOff()
{
    Serial.println("off");
    LEDisON = 0;
    int b;
    for(b=255;b>=0;b--)
    {
        for(i=0;i<LNUM;i++)
        {
            analogWrite(LED[i],b);
        }
        delay(10);
    }
    digitalWrite(LED[0],LOW);
    digitalWrite(LED[1],LOW);
    digitalWrite(LED[2],LOW);
    digitalWrite(LED[3],LOW);
}
void setup()
{
    pinMode(11,OUTPUT);//Relay
    pinMode(INPUTKUNCI,INPUT);
    pinMode(INPUTMEDALI,INPUT);
    
    digitalWrite(INPUTKUNCI,HIGH);
    digitalWrite(INPUTMEDALI,HIGH);
    
    Serial.begin(9600);
}
void loop()
{
    if (digitalRead(INPUTKUNCI)==LOW)
    {
        digitalWrite(13,HIGH);
        digitalWrite(11,LOW);//Relay
    }
    else
    {
        digitalWrite(13,LOW);
        digitalWrite(11,HIGH);//Relay
    }
    if (digitalRead(INPUTMEDALI)==LOW)
    {
        if(LEDisON==0)
            LedOn();
    }
    else
    {
        if(LEDisON==1)
            LedOff();
    }
}
