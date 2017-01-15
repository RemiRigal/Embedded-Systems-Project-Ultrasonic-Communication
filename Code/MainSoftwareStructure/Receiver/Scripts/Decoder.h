#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <vector>

class Decoder
{
public:
    Decoder();
    ~Decoder();
    static std::string decodeMessage(std::vector<int> message);
	static bool isStartOfText(vector<int> digits);
    static bool isEndOfText(vector<int> digits);

};

#endif // DECODER_H