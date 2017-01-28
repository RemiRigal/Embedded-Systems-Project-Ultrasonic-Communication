
#include <cstdio>
#include "miosix.h"
#include "Serial.h"
#include "USTransmitter.h"
#include "Encoder.h"

using namespace std;
using namespace miosix;

int main() {
    Serial serial;
	USTransmitter transmitter;
	
	for (;;) {
		int bufferSize = serial.readLine();
		if (bufferSize >= 0) {
			string message = serial.getBuffer();
			vector<int> encodedMessage = Encoder::encodeMessage(message);
			serial.write("Transmission...");
			transmitter.transmit(encodedMessage);
			serial.write("Done.");
		}
	}
	return 0;
}