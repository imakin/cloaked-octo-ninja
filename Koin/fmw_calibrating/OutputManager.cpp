#include "OutputManager.h"


Outputs::Outputs() 
{
}

void Outputs::setAll() 
{
	node *t = pins.myFront();
	while (t!=NULL)
	{
		digitalWrite(t->value,HIGH);
		t = t->next;
	}
}
void Outputs::clearAll() 
{
	node *t = pins.myFront();
	while (t!=NULL)
	{
		digitalWrite(t->value,LOW);
		t = t->next;
	}
}
void Outputs::add(int pin) 
{
	pins.pushback(pin);
	pinMode(pin,OUTPUT);
}
