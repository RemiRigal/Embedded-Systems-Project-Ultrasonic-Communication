#include "encoder.h"
#include <string>

using namespace std;


Encoder::Encoder(string message) {
    messageToEncode = message;
}


Encoder::~Encoder() {
}

vector<int> Encoder::encodeMessage() {
    int letterChoice[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int sizeMessage(messageToEncode.size());
    vector<int> encodingMessageHex;
    for (int i=0; i < sizeMessage; i++) {
        char letter = messageToEncode[i];

        encodingMessageHex.push_back(letterChoice[letter/16]);
        encodingMessageHex.push_back(letterChoice[letter%16]);

    }
    return encodingMessageHex;
}