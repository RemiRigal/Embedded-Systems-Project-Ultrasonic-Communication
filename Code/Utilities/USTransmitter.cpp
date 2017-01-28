#include "USTransmitter.h"
#include <cstdio>
#include <miosix.h>

using namespace miosix;

typedef Gpio<GPIOH_BASE, 1> transmitter;

USTransmitter::USTransmitter() {
	transmitter::mode(Mode::OUTPUT);
}

USTransmitter::~USTransmitter() {

}

void USTransmitter::transmit(std::vector<int> message) {
	for (unsigned int i = 0; i < message.size(); i++) {
		int nbSquaresToTransmit = message[i];
		// Generating a square signal
		generateSquareWave((nbSquaresToTransmit + 1) * SQUARE_MULTIPLIER);
		// Pause that separates characters
		Thread::sleepUntil(getTick() + PAUSE_DURATION);
	}
}

void USTransmitter::generateSquareWave(float nbSquares) {
	long long tick = getTick();
	
	for (int i = 0; i < nbSquares; i++) {
        transmitter::high();
        tick += EMISSION_HALF_PERIOD;
        Thread::sleepUntil(tick);
		
		transmitter::low();
		tick += EMISSION_HALF_PERIOD;
		Thread::sleepUntil(tick);
	}
}