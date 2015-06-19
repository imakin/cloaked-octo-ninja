#include "OutputManager.h"


Outputs::Outputs() 
{
}

void Outputs::setAll() 
{
	node *t = pins.myFront();
	while (t->next!=NULL)
	{
		digitalWrite(t->value,HIGH);
		
		Serial.print(t->value);
		Serial.print(" has been set\n");
		delay(500);
		
		t = t->next;
	}
}
void Outputs::clearAll() 
{
	node *t = pins.myFront();
	while (t->next!=NULL)
	{
		digitalWrite(t->value,LOW);
		
		Serial.print(t->value);
		Serial.print(" has been clear\n");
		delay(500);
		
		t = t->next;
	}
}
void Outputs::add(int pin) 
{
	pins.pushback(pin);
}
