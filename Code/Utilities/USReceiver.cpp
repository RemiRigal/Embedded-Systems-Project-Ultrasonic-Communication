#include "USReceiver.h"
#include "Decoder.h"
#include <miosix.h>
#include <std>

using namespace miosix;


USReceiver::USReceiver() {
	receiver::mode(Mode::INPUT);
}

USReceiver::~USReceiver() {
	
}

std::vector<int> USReceiver::receive() {
	int lastPoll = 0;
	int squareCount = 0;
	int lastCharacter = -1;
	textEnded = false;
	textStarted = false;
	message.clear();
	
	tick = getTick();
	while (!textEnded) {
		tick += POLLING_RATE;
		Thread::sleepUntil(tick);
		
		int poll = receiver::value();
		if (poll == 1) {
			if (lastPoll == 0) { // 1;0
				// New square coming
				squareCount += 1
			}
		} else {
			if (lastPoll == 1) { // 0;1
				// End of square
			} else { // 0;0
				// End of character
				int character = std::round(squareCount / float(100)) - 1;
				
				if (textStarted) {
					if (lastCharacter != -1) {
						textEnded = Decoder.isEndOfText(lastCharacter, character);
						if (!textEnded) {
							message.push_back(lastCharacter);
							message.push_back(character);
						}
						lastCharacter = -1;
					} else {
						lastCharacter = character;
					}
				} else if (lastCharacter != -1) {
					textStarted = Decoder.isStartOfText(lastCharacter, character);
					if (textStarted) {
						lastCharacter = -1;
					}
				} else {
					lastCharacter = character;
				}
				squareCount = 0;
			}
		}
		lastPoll = poll;
	}
	return message;
}