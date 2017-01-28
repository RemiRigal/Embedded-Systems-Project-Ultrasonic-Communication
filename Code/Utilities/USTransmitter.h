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
	
		const int FREQUENCY = 40000;
		const int PAUSE_DURATION = static_cast<int>(168000000 * 0.01); // 10ms
		const int EMISSION_HALF_PERIOD = static_cast<int>(168000000 / (FREQUENCY * 2)); // 12.5µs
		const int SQUARE_MULTIPLIER = 100;
	
		void generateSquareWave(float duration);
};

#endif //USTRANSMITTER_H