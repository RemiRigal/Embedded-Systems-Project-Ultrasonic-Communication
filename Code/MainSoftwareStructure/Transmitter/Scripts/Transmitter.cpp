#include "transmitter.h"
#include "encoder.h"
#include "serial.h"
#include "usTransmitter.h"
#include <string>



Transmitter::Transmitter(){
    Serial serial();                //TODO
    UsTransmitter usTransmitter();  //TODO

}
Transmitter::~Transmitter(){

}

void Transmitter::sendMessage(string message){
    vector<int> encodeMessage = Encoder.encodeMessage(message);
    messages->push_back(encodeMessage);
}
