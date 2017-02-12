#ifndef USTRANSMITTER_H
#define USTRANSMITTER_H

#include <cstdio>
#include <miosix.h>

class USTransmitter {
	
	public:
		USTransmitter();
		~USTransmitter();
		
		void transmit(std::vector<int> message);
		
	private:
		// GPIO pin attached to the transmitter
		//typedef Gpio<GPIOH_BASE, 1> transmitter;
	
		const unsigned int PAUSE_DURATION = 10; // 10ms
		const unsigned int HIGH_EMISSION_HALF_PERIOD = 13; // 13µs
		const unsigned int LOW_EMISSION_HALF_PERIOD = 12; // 12µs
		const int SQUARE_MULTIPLIER = 200;
	
		void generateSquareWave(int nbSquares);
};

#endif //USTRANSMITTER_H