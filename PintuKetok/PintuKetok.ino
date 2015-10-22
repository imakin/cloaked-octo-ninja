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


#define SEQ_LENGTH 4
int seq[SEQ_LENGTH] = {3, 1, 3, 1}; 
/**	contoh: {3, 1, 3, 1}
		3 ketok, 1 ketok, 3 ketok, 1 ketok, (toktoktok tok toktoktok tok)
		ketuk pramuka: {3, 3, 7} 
**/
#define GAP 1000
#define TOLERANCE 500 //-- milisecond
unsigned long lasthit;
unsigned long smallgap;
unsigned long thisgap;
int seq_pos, seq_sub;

unsigned long selisih(unsigned long a, unsigned long b)
{
	//--selisih untuk unsigned
	if (a>b)
		return a-b;
	else
		return b-a;
}

void reset_seq()
{
	seq_sub = 0; seq_pos = 0; 
}

void setup() {
	Serial.begin(9600);
	pinMode(PIN_INPUT, INPUT);
	digitalWrite(PIN_INPUT, PIN_DEFAULT);
	seq_pos = 0;
	seq_sub = 0;
}

void loop () 
{
	while (digitalRead(PIN_INPUT)==PIN_DEFAULT);
	lasthit = millis();
	while (digitalRead(PIN_INPUT)==PIN_ON);
	thisgap = millis() - lasthit;

	if (seq_pos==0 && seq_sub==0)
		smallgap = thisgap;

	if (selisih(thisgap, smallgap)<TOLERANCE)
	{
		//-- small gap, expecting seq_sub complete
		if (seq_sub<seq[seq_pos])
		{
			//-- ok, advance to next
			seq_sub = seq_sub+1;
		}
		else
		{
			reset_seq();
		}
	}
	else
	{
		//-- big gap, expecting seq_pos advance
		if (seq_sub==seq[seq_pos])
		{
			seq_sub = 0;
			seq_pos = seq_pos+1;
			if (seq_pos>=(SEQ_LENGTH-1))
			{
				//-- finish
			}
		}
		else
		{
			reset_seq();
		}
	}
}
