static uint8_t totalUp=0; //-- Total time the selenoid has actived in seconds
void setup()
{
	//-- Both output
	DDRC = DDRC | (1<<7);
	DDRB = DDRB | (1<<7);
	//-- input Pullup
	PORTD = PORTD | (1<<6);
}
void loop()
{
	if (totalUp>120)
		while(1); //-- Lock it to avoid selenoid burn. Restart the system by repowering it
	
	if ( (PIND&(1<<6)) == 0)//-- PIN12 uno is LOW
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
