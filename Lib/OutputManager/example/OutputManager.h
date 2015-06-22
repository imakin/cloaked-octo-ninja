#include <Arduino.h>
#include "Stack.h"
#ifndef OUTPUTMANAGERHPP
#define OUTPUTMANAGERHPP
class Outputs {
	public:
		Stack pins;
		Outputs();
		~Outputs() {}
		void add(int pin);
		void setAll();
		void clearAll();
};
#endif
