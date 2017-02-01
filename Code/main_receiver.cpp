
#include <cstdio>
#include "miosix.h"
#include "Serial.h"
#include "USReceiver.h"
#include "Decoder.h"

using namespace std;
using namespace miosix;

int main() {
    Serial serial;
	serial.write("[I] Initializing Receiver...");
	USReceiver receiver;
	serial.write("[I] Initialized.");
	
	for (;;) {
		serial.write("[I] Waiting for transmission...");
		vector<int> encodedMessage = receiver.receive();
		if (encodedMessage.size() > 0) {
			string message = Decoder::decodeMessage(encodedMessage);
			serial.write("[I] Incoming message: " + message);
		}
	}
	return 0;
}