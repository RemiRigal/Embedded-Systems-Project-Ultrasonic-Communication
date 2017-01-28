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

USReceiver::~USReceiver() {
	
}

std::vector<int> USReceiver::receive() {
	int lastPoll = 0;
	int squareCount = 0;
	int zeroCount = 0;
	int lastCharacter = -1;
	textEnded = false;
	textStarted = false;
	message.clear();
	
	while (!textEnded) {
		delayUs(12);
		
		int poll = receiver::value();
		if (poll == 1) {
			blueLed::high();
			if (zeroCount != 0) {
				zeroCount = 0;
			}
			if (lastPoll == 0) { // 1;0
				// New square coming
				squareCount += 1;
			}
		} else {
			blueLed::low();
			if (lastPoll == 1) { // 0;1
				// End of square
			} else if (squareCount > 50 && zeroCount > 50) { // 0;0
				// End of character
				zeroCount = 0;
				int character = ((squareCount  + 50) / 100) - 1;
				printf("%i\n", character);
				if (textStarted) {
					if (lastCharacter != -1) {
						textEnded = Decoder::isEndOfText(lastCharacter, character);
						if (!textEnded) {
							message.push_back(lastCharacter);
							message.push_back(character);
						}
						lastCharacter = -1;
					} else {
						lastCharacter = character;
					}
				} else if (lastCharacter != -1) {
					textStarted = Decoder::isStartOfText(lastCharacter, character);
					if (textStarted) {
						lastCharacter = -1;
					}
				} else {
					lastCharacter = character;
				}
				squareCount = 0;
			} else if (squareCount > 50) {
				zeroCount++;
			}
		}
		lastPoll = poll;
	}
	return message;
}