#include "decoder.h"
#include <string>

using namespace std;


Decoder::Decoder(std::vector<int> message) {
    messageToDecode = message;
}


Decoder::~Decoder() {
}

string Decoder::decodeMessage() {
    int messageSize = messageToDecode.size();
    if (messageSize < 2){
        throw std::invalid_argument("Received a too small length message");
    }
    string decodingMessage;
    for (int i=0; i < messageSize; i= i+2){
        int firstDigit = messageToDecode[i];
        int secondDigit = messageToDecode[i+1];
        if (abs(firstDigit) > 7 || abs(secondDigit)> 15){
            throw std::invalid_argument("Not an hexadecimal digit");
        }
        char letter = (char)(firstDigit*16 + secondDigit);

        decodingMessage += letter;
    }
    return decodingMessage;
}