
#include <cstdio>
#include "miosix.h"
#include "Serial.h"
#include "USReceiver.h"
#include "Decoder.h"

using namespace std;
using namespace miosix;

int main() {
    Serial serial;
	USReceiver receiver;
	
	for (;;) {
		vector<int> encodedMessage = receiver.receive();
		string message = Decoder::decodeMessage(encodedMessage);
		serial.write("Incoming message: " + message);
	}
	return 0;
}