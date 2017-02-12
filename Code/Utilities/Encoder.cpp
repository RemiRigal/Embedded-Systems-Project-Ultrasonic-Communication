#include "encoder.h"
#include <string>

using namespace std;


Encoder::Encoder() {
}


Encoder::~Encoder() {
}

vector<int> Encoder::encodeMessage(string messageToEncode) {
    int sizeMessage = messageToEncode.size();
    vector<int> encodingMessageHex;
	
	encodingMessageHex.push_back(0); // Start encoding number in hexa
    encodingMessageHex.push_back(2); // : '02'
	
    for (int i = 0; i < sizeMessage; i++) {
        char letter = messageToEncode[i];
		if (letter > 127) {
			encodingMessageHex.push_back(5); 		// Hexa number 
			encodingMessageHex.push_back(15);	   // for '?' 
		} else {
			encodingMessageHex.push_back(letter/16);
			encodingMessageHex.push_back(letter%16);
		}
    }
	encodingMessageHex.push_back(0); // End encoding number in hexa
    encodingMessageHex.push_back(3); // : '03'
	
    return encodingMessageHex;
}