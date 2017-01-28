
#include <cstdio>
#include "miosix.h"
#include "Serial.h"
#include "USTransmitter.h"
#include "Encoder.h"

using namespace std;
using namespace miosix;

int main() {
	Serial serial;
	serial.write("[I] Initializing...");
	USTransmitter transmitter;
	serial.write("[I] Initialized.");
	
	for (;;) {
		serial.write("[I] Waiting for message");
		int bufferSize = serial.readLine();
		if (bufferSize >= 0) {
			string message = serial.getBuffer();
			serial.write("Received: " + message);
			vector<int> encodedMessage = Encoder::encodeMessage(message);
			
			serial.write("[I] Transmission...");
			transmitter.transmit(encodedMessage);
			serial.write("[I] Done.");
		}
	}
	return 0;
}