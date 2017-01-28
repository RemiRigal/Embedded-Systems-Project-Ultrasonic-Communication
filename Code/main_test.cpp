
#include <cstdio>
#include <std>
#include "miosix.h"
#include "Serial.h"

using namespace std;
using namespace miosix;

typedef Gpio<GPIOD_BASE, 13> receiver;
typedef Gpio<GPIOD_BASE, 15> blueLed;

int main() {
    Serial serial;
	
	blueLed::mode(Mode::OUTPUT);
	receiver::mode(Mode::INPUT);
	
	for (;;) {
		if (receiver::value() == 1) {
			blueLed::high();
			Thread::sleep(1000);
		}
	}
}
