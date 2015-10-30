#define PIN_INPUT 4

//~ #define SENSOR_PULL_DOWN

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
int seqpin[SEQ_LENGTH] = {2, 3, 4, 5}; //-- pin reading tombol

int seq_pos, seq_subpos;

int expectpin;
int readpin;

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
	seq_subpos = 1; seq_pos = 0; 
}

int expectInput()
{
	int i;
	for (i = 0;i<SEQ_LENGTH; i++)
	{
		if (digitalRead(seqpin[i])==PIN_ON)
		{
			delay(100);
			if (digitalRead(seqpin[i])==PIN_ON)
				return seqpin[i];
		}
	}
	return -1;
}


void setup() {
	Serial.begin(9600);
	for (int i=0; i<SEQ_LENGTH; i++)
	{
		pinMode(seqpin[i], INPUT);
		digitalWrite(seqpin[i], HIGH);
	}
	seq_pos = 0;
	seq_subpos = 0;
}

void loop () 
{	
	expectpin = seqpin[seq_pos];
	readpin = (-1);
	while(readpin==(-1))
		readpin = expectInput();
	if (readpin==expectpin)
	{
		seq_subpos += 1;
		if (seq_subpos > seq[seq_pos])
		{
			seq_pos += 1;
			seq_subpos = 1;
			if (seq_pos>=SEQ_LENGTH)
			{
				//sequence bener, aksi
				Serial.println("OKE");
				reset_seq();
			}
		}
	}
	else
	{
		if (seq_pos==1 && readpin==seqpin[0])
		{
			seq_pos = 0;
			seq_subpos = seq[seq_pos];
		}
		else
			reset_seq();
		//~ if (readpin==seqpin[0])
			//~ seq_subpos += 1;
	}
	while(expectInput()==readpin);
	
	Serial.print(seq_subpos);
	Serial.print("-");
	Serial.print(seq_pos);
	Serial.print(" [ ");
	Serial.print(expectpin);
	Serial.print(" ");
	Serial.println(seq[seq_pos]);
	
}
