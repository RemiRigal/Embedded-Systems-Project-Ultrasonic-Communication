// TODO : define test mode
// #define MODE_SQUARE40Hz
// #define MODE_ASCII_TRANSMITTER
// #define MODE_ASCII_RECEIVER
// #define MODE_STATISTICS_TRANSMITTER
// #define MODE_STATISTICS_RECEIVER

// how many char to send to test transmission with MODE_STATISTICS
#define CHAR_MULTIPLIER 20
#define FIRST_ASCII 32
#define LAST_ASCII 126
#define FIRST_DIGIT 0
#define LAST_DIGIT 15

#include <string>
#include "miosix.h"
#include "Serial.h"
#include "Encoder.h"
#include "USTransmitter.h"
#include "Decoder.h"
#include "USReceiver.h"

using namespace std;
using namespace miosix;

typedef Gpio<GPIOA_BASE, 0> transmitterPort;
typedef Gpio<GPIOD_BASE, 15> blueLed;

#ifdef MODE_STATISTICS_RECEIVER
void	displayStatistics(unsigned int nbDigitOK[], unsigned int nbDigitInf[], unsigned int nbDigitSup[])
{
	Serial serial;
	serial.write("\nStatistics of the transmission:\n");
	serial.write(" digit |  =  |  <  |  >  |  %%  ");
	serial.write(" ----- | --- | --- | --- | --- ");
		
	for (unsigned char d=FIRST_DIGIT; d<=LAST_DIGIT; d++)
	{
		float stat = (float)nbDigitOK[d]/(float)CHAR_MULTIPLIER*100.0;
		printf(" %hi  |  %d  |  %d  |  %d  |  %03f  \n", d, nbDigitOK[d], nbDigitInf[d], nbDigitSup[d], stat);
	}
}
#endif

int main() {
    Serial serial;
	bool done = false;
	
	#ifdef MODE_SQUARE40Hz
	blueLed::mode(Mode::OUTPUT);
	transmitterPort::mode(Mode::OUTPUT);
	serial.write("[I] Sending a 40Hz signal...");
	#endif
	
	while (!done) 
	{
		#ifdef MODE_SQUARE40Hz
		blueLed::high();
		transmitterPort::high();
		delayUs(13);
		blueLed::low();
		transmitterPort::low();
		delayUs(12);
		#endif
		
		#if defined MODE_ASCII_TRANSMITTER || defined MODE_STATISTICS_TRANSMITTER
		serial.write("[I] Initializing Transmitter...");
		USTransmitter transmitter;
		serial.write("[I] Initialized.");
		#endif
	
		#if defined MODE_ASCII_TRANSMITTER || defined MODE_ASCII_RECEIVER
		serial.write("[I] Initializing ASCII test message...");
		string sentMessage = "";
		// create a message containing ASCII characters from ' ' to '~'
		for (unsigned char i=FIRST_ASCII; i<=LAST_ASCII; i++) {
				sentMessage += i;
		}
		#endif

		#ifdef MODE_ASCII_TRANSMITTER
		serial.write("\nType ENTER to start statistics");
		serial.readLine();
		
		vector<int> encodedMessage = Encoder::encodeMessage(sentMessage);
		
		serial.write("[I] Transmission of: " + sentMessage);
		transmitter.transmit(encodedMessage);
		serial.write("[I] Done.");
		#endif
		
		#ifdef MODE_STATISTICS_TRANSMITTER
		serial.write("\nType ENTER to start statistics");
		serial.readLine();
		
		// test every ASCII character from ' ' to '~'
		for (unsigned char d=FIRST_DIGIT; d<=LAST_DIGIT; d++)
		{
			printf("[I] Initializing message containing n=%d times the digit '%hi'...\n", CHAR_MULTIPLIER, d);
			vector<int> encodedMessage;
			for (unsigned int u=0; u<CHAR_MULTIPLIER; u++)
				encodedMessage.push_back(d);
			
			serial.write("[I] Transmission.");
			transmitter.transmit(encodedMessage);
			serial.write("[I] Done.");
			delayMs(100);
		}
		#endif
		
		#if defined MODE_ASCII_RECEIVER || defined MODE_STATISTICS_RECEIVER
		serial.write("[I] Initializing Receiver...");
		USReceiver receiver;
		serial.write("[I] Initialized.");
		#endif
		
		#ifdef MODE_ASCII_RECEIVER
		serial.write("[I] Waiting for transmission of the ASCII test message...");
		vector<int> encodedMessage = receiver.receive();
		string receivedMessage = Decoder::decodeMessage(encodedMessage);
		serial.write("[I] Incoming message: " + receivedMessage);
		
		if (!sentMessage.compare(receivedMessage))
			serial.write("[OK] Successful transmission.");
		else
			serial.write("[ERR] Error(s) in transmission:\n\texpected: " + sentMessage
			+ "\n\treceived: " + receivedMessage);
		#endif
		
		#ifdef MODE_STATISTICS_RECEIVER
		unsigned int nbDigitOK [LAST_DIGIT-FIRST_DIGIT + 1] = { };
		unsigned int nbDigitInf [LAST_DIGIT-FIRST_DIGIT + 1] = { };
		unsigned int nbDigitSup [LAST_DIGIT-FIRST_DIGIT + 1] = { };
		
		// test every ASCII character from ' ' to '~'
		for (unsigned char d=FIRST_DIGIT; d<=LAST_DIGIT; d++)
		{
			printf("[I] Waiting for transmission of the message containing n=%d times the digit c='%hi'...\n", CHAR_MULTIPLIER, d);
			vector<int> encodedMessage = receiver.receive(CHAR_MULTIPLIER);
			printf("[I] Message received: ");
			for (unsigned int i=0; i<encodedMessage.size(); i++)
				printf("%hi ", encodedMessage[i]);
			printf("\n");
			
			// analyze result
			for (unsigned int u=0; u<CHAR_MULTIPLIER; u++)
			{
				if (encodedMessage[u] == d) nbDigitOK[d]++;
				else if (encodedMessage[u] < d) nbDigitInf[d]++;
				else if (encodedMessage[u] > d) nbDigitSup[d]++;
			}
		}
		displayStatistics(nbDigitOK, nbDigitInf, nbDigitSup);
		#endif
		
		#if defined MODE_ASCII_TRANSMITTER || defined MODE_ASCII_RECEIVER \
			|| defined MODE_STATISTICS_TRANSMITTER || defined MODE_STATISTICS_RECEIVER
		serial.write("\nType 'r' to retry, 'q' to quit");
		int size = 0;
		for (;;)
		{
			size = serial.readLine();
			if (size == 1)
			{
				if (!serial.getBuffer().compare("q"))
				{
					done = true;
					break;
				}
				else if (!serial.getBuffer().compare("r"))
					break;
			}
		}
		#endif
	}
	
	return 0;
}
