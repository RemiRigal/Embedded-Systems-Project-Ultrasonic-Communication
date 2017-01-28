#include "USTransmitter.h"
#include <miosix.h>

using namespace miosix;


USTransmitter::USTransmitter() {
	transmitter::mode(Mode::OUTPUT);
}

USTransmitter::~USTransmitter() {

}

void USTransmitter::transmit(int[] message) {
	long long tick = getTick();
	for (int i = 0; i < message.length; i++) {
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