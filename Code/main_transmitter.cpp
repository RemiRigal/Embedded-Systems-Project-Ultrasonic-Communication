
#include <cstdio>
#include <std>
#include "miosix.h"
#include "Serial.h"
#include "Transmitter.h"
#include "Encoder.h"

using namespace std;
using namespace miosix;

int main() {
    Serial serial;
	Transmitter transmitter;
	
	for (;;) {
		int bufferSize = serial.readLine();
		if (bufferSize >= 0) {
			string message = serial.getBuffer();
			vector<int> encodedMessage = Encoder.encodeMessage(message);
			serial.write("Transmission...");
			transmitter.transmit(encodedMessage);
			serial.write("Done.");
		}
	}
}
