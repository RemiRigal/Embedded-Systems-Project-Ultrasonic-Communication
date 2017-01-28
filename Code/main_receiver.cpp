
#include <cstdio>
#include <std>
#include "miosix.h"
#include "Serial.h"
#include "Receiver.h"
#include "Decoder.h"

using namespace std;
using namespace miosix;

int main() {
    Serial serial;
	Receiver receiver;
	
	for (;;) {
		vector<int> encodedMessage = receiver.receive();
		string message = Decoder.decodeMessage(encodedMessage);
		serial.write("Incoming message: " + message);
	}
}