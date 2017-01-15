#include "decoder.h"
#include <string>

using namespace std;


Decoder::Decoder() {
}


Decoder::~Decoder() {
}

string Decoder::decodeMessage(vector<int> messageToDecode) {
    int messageSize = messageToDecode.size();
    if (messageSize < 2){
        Serial.write("Received a too small length message"); 		// TODO
        return "?";
    }
    string decodingMessage;
    for (int i=0; i < messageSize; i= i+2){
        int firstDigit = messageToDecode[i];
        int secondDigit = messageToDecode[i+1];
		char letter;
        if (abs(firstDigit) > 7 || abs(secondDigit)> 15){
           Serial.write("Not an hexadecimal digit"); 				// TODO
           letter = "?";
        }
		else{
				letter = (char)(firstDigit*16 + secondDigit);
		}    
        decodingMessage += letter;
    }
    return decodingMessage;
}

bool Decoder::isStartOfText(vector<int> digits){
    if (digits.size() < 2){
        Serial.write("Received a too small length digits for start"); // TODO
    }
    else{
        return (digits[0] == 0 && digits[1] == 2);
    }
    return false;
}

bool Decoder::isEndOfText(vector<int> digits){
    if (digits.size() < 2){
        Serial.write("Received a too small length digits for stop"); // TODO
    }
    else{
        return (digits[0] == 0 && digits[1] == 3);
    }
    return false;
}