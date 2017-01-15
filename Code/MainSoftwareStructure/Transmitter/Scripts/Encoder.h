#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <vector>


class Encoder {
public:
    Encoder();
    ~Encoder();
    static std::vector<int> encodeMessage(std::string message);
};

#endif // ENCODER_H
