static uint8_t totalUp=0; //-- Total time the selenoid has actived in seconds
void setup()
{
	//-- Both output
	DDRC = DDRC | (1<<7);//-- Leonardo LED
	DDRB = DDRB | (1<<7);//-- Relay
	//-- input Pullup
	//~ PORTE = PORTE | (1<<6);//-- Leonardo PIN7
	//~ PORTD = PORTD | (1<<7);//-- Leonardo PIN6
	//~ PORTC = PORTC | (1<<6);//-- Leonardo PIN5
	//~ PORTD = PORTD | (1<<4);//-- Leonardo PIN4
	pinMode(7,INPUT);
	pinMode(6,INPUT);
	pinMode(5,INPUT);
	pinMode(4,INPUT);
	digitalWrite(7,HIGH);
	digitalWrite(6,HIGH);
	digitalWrite(5,HIGH);
	digitalWrite(4,HIGH);
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
		PORTB = PORTB & ~(1<<7);
		delay(20000);
		totalUp += 20;
		PORTC = PORTC | (1<<7); //-- revert & close relay connections
		PORTB = PORTB | (1<<7);
	}
	else
	{
		PORTC = PORTC | (1<<7); //-- close relay connections
		PORTB = PORTB | (1<<7);
	}
}
