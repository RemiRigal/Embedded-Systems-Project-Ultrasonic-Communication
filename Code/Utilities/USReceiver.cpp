#include "USReceiver.h"
#include "Decoder.h"
#include <cstdio>
#include <miosix.h>

using namespace miosix;

typedef Gpio<GPIOA_BASE, 0> receiver;
typedef Gpio<GPIOD_BASE, 15> blueLed;

USReceiver::USReceiver() {
	receiver::mode(Mode::INPUT);
	blueLed::mode(Mode::OUTPUT);
}

USReceiver::~USReceiver() {}

std::vector<int> USReceiver::receive() {
	message.clear();
	int lastDigit = -1;
	textEnded = false;
	textStarted = false;
	
	while (!textEnded) {
		int digit;
		try {
			digit = receiveDigit();
		} catch (TimeOutException e) {
			if (textStarted) {
				printf("[E] Timeout");
				message.clear();
				return message;
			}
			continue;
		}
		
		if (lastDigit == -1) {
			lastDigit = digit;
		} else {
			if (textStarted) {
				textEnded = Decoder::isEndOfText(lastDigit, digit);
				if (!textEnded) {
					message.push_back(lastDigit);
					message.push_back(digit);
					lastDigit = -1;
				}
			} else {
				textStarted = Decoder::isStartOfText(lastDigit, digit);
				lastDigit = -1;
			}
		}
	}
	return message;
}

std::vector<int> USReceiver::receive(unsigned int nbDigits) {
	message.clear();
	while (message.size() < nbDigits) {
		int digit;
		try {
			digit = receiveDigit();
		} catch (TimeOutException e) {
			message.clear();
			return message;
		}
		message.push_back(digit);
	}
	return message;
}

int USReceiver::receiveDigit() {
	bool isCounting = false;
	int zeroCount = 0;
	int squareCount = 0;
	bool isOdd = false;
	
	for (;;) {
		if (isOdd) {
			delayUs(POLLING_RATE + 1);
		} else {
			delayUs(POLLING_RATE);
		}
		isOdd = !isOdd;
		
		int poll = receiver::value();
		
		if (poll == 0) {
			blueLed::low();
			zeroCount++;
		} else {
			blueLed::high();
			zeroCount = 0;
		}
		
		if (zeroCount > TIMEOUT * FREQUENCY * 2) {
			throw TimeOutException();
		}
		
		if (isCounting && zeroCount < 200) {
			if (isOdd) {
				squareCount++;
			}
		} else if (isCounting) {
			int digit = ((squareCount - (zeroCount / 2) + HALF_SQUARE_MULTIPLIER) / SQUARE_MULTIPLIER) - 1;
			if (digit < 0) {
				squareCount = 0;
				isCounting = false;
			} else {
				printf("[I] Digit: %i\n", digit);
				return digit;
			}
		} else if (poll == 1) {
			isCounting = true;
		}
	}
}





































>>>>>>> 5bc5da9... [USReceiver] Second algorithm test
