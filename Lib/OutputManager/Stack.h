#include <Arduino.h>
#ifndef STACKHPP
#define STACKHPP
struct node {
	int value;
	node *next;
	node *prev;
};

class Stack {
	node *front;
	node *rear;
	unsigned int num;
	public:
	Stack();
	~Stack() {}
	void pushback(int val);
	int popback();
	unsigned int size();
	node *myFront() {return front;}
	node *myRear() {return rear;}
};
#endif
