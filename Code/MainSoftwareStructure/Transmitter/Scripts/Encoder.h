#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <vector>


class Encoder {
public:
    Encoder(std::string message);
    ~Encoder();
    std::vector<int> encodeMessage();

protected:
    std::string messageToEncode;
};

#endif // ENCODER_H
