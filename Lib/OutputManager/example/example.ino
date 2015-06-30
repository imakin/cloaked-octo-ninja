#include "Stack.h"
String inputString = "";
boolean stringComplete = false;

Stack s;

char ReadInput() {
	while (!Serial.available());
	char inChar = (char)Serial.read(); 
	Serial.read();//--"the newline"
	Serial.println(inChar);
	return inChar;
}

void setup() {
	Serial.begin(9600);
	delay(2000);
	Serial.println("BISMILLAH");
	Serial.println("BISMILLAH2");
	node *p = NULL;
	while (1) {
		Serial.println("cmd: 1=push 2=pop 3=draw");
		Serial.println("v=value(of_current_pointer) b=prev n=next");
		
		char inp=ReadInput();
		//~ delay(1000);
		if (inp=='1')
		{
			Serial.println("input number...");
			int v = Serial.parseInt();
			s.pushback(v);
			Serial.print("Pushed: ");
			Serial.println(v);
		}
		else if (inp=='2')
		{
			Serial.print("Poped: ");
			Serial.println(s.popback());
		}
		else if (inp=='3')
		{
			node *t = s.myFront();
			while (t!=NULL)
			{
				Serial.print(t->value);
				Serial.print(" ");
				t = t->next;
			}
			Serial.print("\n");
			delete t;
		}
		else if (inp=='v')
		{
			if (p!=NULL)
				Serial.println(p->value);
			else
			{
				p = s.myFront();
				Serial.println("front");
				Serial.println(p->value);
			}
		}
		else if (inp=='n')
		{
			if (p->next != NULL)
				p = p->next;
		}
		else if (inp=='b')
		{
			if (p->prev != NULL)
				p = p->prev;
		}
	}
}

void loop() {
	
}

