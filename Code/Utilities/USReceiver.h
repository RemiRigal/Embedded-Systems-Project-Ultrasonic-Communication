#ifndef USRECEIVER_H
#define USRECEIVER_H

#include <cstdio>
#include <miosix.h>

#define nbLastPolls 5

class USReceiver {
	
	public:
		USReceiver();
		~USReceiver();
		
		std::vector<int> receive();
		std::vector<int> receive(unsigned int nbDigits);
		
	private:
		int receiveDigit();
	
		const int FREQUENCY = 40000;
		const int POLLING_RATE = 1000000 / (2 * FREQUENCY);
		const int SQUARE_MULTIPLIER = 200;
		const int HALF_SQUARE_MULTIPLIER = SQUARE_MULTIPLIER / 2;
		const int TIMEOUT = 5;
		
		bool textEnded = false;
		bool textStarted = false;
		std::vector<int> message;
};

class TimeOutException {};

#endif //USRECEIVER_H