#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <vector>

class Decoder
{
public:
    Decoder(std::vector<int> message);
    ~Decoder();
    std::string decodeMessage();

private:
    std::vector<int> messageToDecode;

};

#endif // DECODER_H