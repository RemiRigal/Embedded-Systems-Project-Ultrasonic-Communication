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
		//printf("Transmitting: %i\n", nbSquaresToTransmit);
		generateSquareWave((nbSquaresToTransmit + 1) * SQUARE_MULTIPLIER);
		
		// Pause that separates characters
		//printf("Pause\n");
		delayMs(PAUSE_DURATION);
	}
}

void USTransmitter::generateSquareWave(int nbSquares) {
	for (int i = 0; i < nbSquares; i++) {
        transmitter::high();
		delayUs(HIGH_EMISSION_HALF_PERIOD);
		
		transmitter::low();
		delayUs(LOW_EMISSION_HALF_PERIOD);
	}
}