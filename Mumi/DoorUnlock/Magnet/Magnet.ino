#define SELENOID 11
#define LAMPUMUMI 10
static uint8_t totalUp=0; //-- Total time the selenoid has actived in seconds

void setup()
{
	//-- Both output
	DDRC = DDRC | (1<<7);//-- Leonardo LED
	pinMode(SELENOID, OUTPUT);
	pinMode(LAMPUMUMI, OUTPUT);
	//-- input Pullup
	pinMode(7,INPUT);
	pinMode(6,INPUT);
	pinMode(5,INPUT);
	pinMode(4,INPUT);
	pinMode(3,INPUT); //--- this one for medallion
	digitalWrite(7,HIGH);
	digitalWrite(6,HIGH);
	digitalWrite(5,HIGH);
	digitalWrite(4,HIGH);
	digitalWrite(3,HIGH);
}
void loop()
{
	if (totalUp>120)
		while(1); //-- Lock it to avoid selenoid burn. Restart the system by repowering it
	
	if (
			digitalRead(7)==LOW &&
			digitalRead(6)==LOW &&
			digitalRead(5)==LOW &&
			digitalRead(4)==LOW
		)
	{
		PORTC = PORTC & ~(1<<7); //-- Fire up relay to activate selenoid
		digitalWrite(SELENOID,LOW);
		digitalWrite(LAMPUMUMI,HIGH);
		delay(20000);
		totalUp += 20;
		PORTC = PORTC | (1<<7); //-- revert & close relay connections
		digitalWrite(11,HIGH);
	}
	else
	{
		PORTC = PORTC | (1<<7); //-- close relay connections
		digitalWrite(11,HIGH);
	}
}
