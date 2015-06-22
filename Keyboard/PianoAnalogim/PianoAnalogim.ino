/*
Working version of piano
 */

// These constants won't change.  They're used to give names
// to the pins used:
//const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

const int outputPin = 12; //output for the relay
  
int toneSequence[] = {7,1,5,1,4,2,1,5}; //Put this in reverse of the actual note
int length = 8;
int pianoPress[] = {99,99,99,99,99,99,99,99};
int index = 0; //analog input pin
int lastActive = -99; //remember the last active input pin;

int sensorValue = 0;        // value read from the pot
int endSearch = 0;         // If sequence found, stop the whole operation. Open door.
int finish = 0;

void setup() {
	pinMode(outputPin, OUTPUT);
	// initialize serial communications at 9600 bps:
	//Serial.begin(9600); 
}

void loop() {
	for (index = 0; index<8; index++){
		// read the analog in value:
		sensorValue = analogRead(index);

		if (sensorValue > 600 & finish != 1 & lastActive != index){ //prevent samevalue hold
			for(int n=length - 1; n > 0; n--){
				pianoPress[n] = pianoPress[n-1]; // shifting done here
			}
			pianoPress[0] = index; // and here
			lastActive = index;  
		}

		int match = 1;
		for (int n=0; n<length;n++)
		{    
			if (pianoPress[n] != toneSequence[n]) {
				match = 0;
			}
		//endSearch = 1;
		}
		if (match == 1){
			digitalWrite(outputPin, HIGH);
			finish = 1;
		}
	}
}
