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
		const int POLLING_RATE = static_cast<int>(168000000 / FREQUENCY);
		
		bool textEnded = false;
		bool textStarted = false;
		std::vector<int> message;
		
		long long tick = 0;
};

#endif //USRECEIVER_H