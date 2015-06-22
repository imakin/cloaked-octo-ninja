#include "Stack.h"

Stack::Stack() {
	front = NULL;
	rear = NULL;
	num = 0;
}
void Stack::pushback(int val){
	node *t = new node();
	t->value = val;
	t->next = NULL;
	if (front==NULL)
	{
		front = t;
	}
	else
	{
		rear->next = t;
	}
	t->prev = rear;
	rear = t;
	num+=1;
}
int Stack::popback(){
	//~ node *t = new node();
	int val;
	if (rear==NULL) {
		//~ throw 1;
	}
	else {
		val = rear->value;
		rear = rear->prev;
		delete rear->next;
		rear->next = NULL;
	}
	return val;
}

unsigned int Stack::size() {
	return num;
}

/** //
int Stack::popfront(){
	node t = new node();
	int val;
	if (front==NULL) {
		val = 0;
	}
	else {
		t = front;
		val = t->value;
		front = front->next;
	}
	return val;
}
//*/
