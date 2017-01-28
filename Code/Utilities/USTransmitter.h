#ifndef USTRANSMITTER_H
#define USTRANSMITTER_H

#include <miosix.h>
#include <std>

class USTransmitter {
	
	public:
		USTransmitter();
		~USTransmitter();
		
		void transmit(std::vector<int> message);
		
	private:
		// GPIO pin attached to the transmitter
		typedef Gpio<GPIOD_BASE, 15> transmitter;
	
		const int FREQUENCY = 40000;
		const int PAUSE_DURATION = static_cast<int>(TICK_FREQ * 0.01); // 10ms
		const int EMISSION_HALF_PERIOD = static_cast<int>(TICK_FREQ / (FREQUENCY * 2)); // 12.5µs
		const int SQUARE_MULTIPLIER = 100;
	
		void generateSquareWave(float duration);
	
}

#endif //USTRANSMITTER_H