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
		static bool isStartOfText(int firstDigit, int secondDigit);
		static bool isEndOfText(int firstDigit, int secondDigit);

};

#endif // DECODER_H