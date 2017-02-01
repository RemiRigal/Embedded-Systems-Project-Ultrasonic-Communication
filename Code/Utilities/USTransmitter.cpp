#include "USTransmitter.h"
#include <cstdio>
#include <miosix.h>

using namespace miosix;

typedef Gpio<GPIOA_BASE, 0> transmitter;
typedef Gpio<GPIOD_BASE, 15> blueLed;

USTransmitter::USTransmitter() {
	transmitter::mode(Mode::OUTPUT);
	blueLed::mode(Mode::OUTPUT);
}

USTransmitter::~USTransmitter() {

}

void USTransmitter::transmit(std::vector<int> message) {
	for (unsigned int i = 0; i < message.size(); i++) {
		int nbSquaresToTransmit = message[i];
		// Generating a square signal
		generateSquareWave((nbSquaresToTransmit + 1) * SQUARE_MULTIPLIER);

		// Pause that separates characters
		delayMs(PAUSE_DURATION);
	}
}

void USTransmitter::generateSquareWave(int nbSquares) {
	for (int i = 0; i < nbSquares; i++) {
		transmitter::high();
		blueLed::high();
		delayUs(HIGH_EMISSION_HALF_PERIOD);

		transmitter::low();
		blueLed::low();
		delayUs(LOW_EMISSION_HALF_PERIOD);
	}
}
