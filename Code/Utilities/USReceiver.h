#ifndef USRECEIVER_H
#define USRECEIVER_H

#include <cstdio>
#include <miosix.h>

class USReceiver {
	
	public:
		USReceiver();
		~USReceiver();
		
		std::vector<int> receive();
		
	private:
		//Gpio<GPIOH_BASE, 1> receiver;
	
		const int FREQUENCY = 40000;
		const int POLLING_RATE = 1000000 / FREQUENCY;
		const int SQUARE_MULTIPLIER = 2000;
		const int HALF_SQUARE_MULTIPLIER = SQUARE_MULTIPLIER / 2;
		
		bool textEnded = false;
		bool textStarted = false;
		std::vector<int> message;
		
		long long tick = 0;
};

#endif //USRECEIVER_H