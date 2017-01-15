#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <iostream>
#include <vector>
#include <list>

class Transmitter
{
public:
    Transmitter();
    ~Transmitter();
    void sendMessage(std::string message);
    list<vector<int>> *messages;
    //TODO mutex to access the list
    //TODO reference to the Object Serial
};

#endif // TRANSMITTER_H