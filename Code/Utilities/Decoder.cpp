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
        return "?";
    }
    string decodingMessage;
    for (int i=0; i < messageSize; i= i+2){
        int firstDigit = messageToDecode[i];
        int secondDigit = messageToDecode[i+1];
		char letter;
        if (abs(firstDigit) > 7 || abs(secondDigit)> 15){
           letter = "?";
        }
		else{
				letter = (char)(firstDigit*16 + secondDigit);
		}    
        decodingMessage += letter;
    }
    return decodingMessage;
}

bool Decoder::isStartOfText(int firstDigit, int secondDigit){
        return (digits[0] == 0 && digits[1] == 2);
}

bool Decoder::isEndOfText(int firstDigit, int secondDigit){
        return (firstDigit == 0 && secondDigit == 3);
}