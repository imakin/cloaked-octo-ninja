#define PIN_INPUT 4

#define SENSOR_PULL_DOWN

#ifdef SENSOR_PULL_DOWN
	#define PIN_DEFAULT LOW
	#define PIN_ON	HIGH
#else
	//-- pull up
	#define PIN_DEFAULT HIGH
	#define PIN_ON	LOW
#endif

unsigned long lasthit;

#define SEQ_LENGTH 3
int seq[SEQ_LENGTH] = {3, 1, 3, 1}; 
/**	contoh: {3, 1, 3, 1}
		3 ketok, 1 ketok, 3 ketok, 1 ketok, (toktoktok tok toktoktok tok)
		ketuk pramuka: {3, 3, 7} 
**/
#define GAP 1000
unsigned long smallgap;
int seq_pos, seq_sub;

void setup() {
	Serial.begin(9600);
	pinMode(PIN_INPUT, INPUT);
	digitalWrite(PIN_INPUT, PIN_DEFAULT);
	seq_pos = 0;
	seq_sub = 0;
}

void loop () 
{
	lasthit = millis();
	if (digitalRead(PIN_INPUT, PIN_ON))
	{
		while (digitalRead(PIN_INPUT, PIN_ON));
		smallgap = 
	}
}
