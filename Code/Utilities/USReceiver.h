#ifndef USRECEIVER_H
#define USRECEIVER_H

#include <miosix.h>
#include <std>

class USReceiver {
	
	public:
		USReceiver();
		~USReceiver();
		
		std::vector<int> receive();
		
	private:
		typedef Gpio<GPIOH_BASE, 1> receiver;
	
		const int FREQUENCY = 40000;
		const int POLLING_RATE = static_cast<int>(TICK_FREQ / FREQUENCY);
		
		bool textEnded = false;
		bool textEnded = false;
		std::vector<int> message;
		
		long long tick = 0;
}

#endif //USRECEIVER_H