#ifndef USRECEIVER_H
#define USRECEIVER_H

class USReceiver {
	
	public:
		USReceiver();
		~USReceiver();
		
		std::vector<int> receive();
		
	private:
		typedef Gpio<GPIOD_BASE, 15> receiver;
	
		const int FREQUENCY = 40000;
		const int POLLING_RATE = static_cast<int>(TICK_FREQ / FREQUENCY);
		
		bool textEnded = false;
		bool textEnded = false;
		std::vector<int> message;
		
		long long tick = 0;
}

#endif //USRECEIVER_H