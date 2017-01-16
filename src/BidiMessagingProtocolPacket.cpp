//
// Created by romybu on 14/01/17.
//

#include "BidiMessagingProtocolPacket.h"

void BidiMessagingProtocolPacket::readFromKeyboard(string line) {
    string _command="";
    string _name="";
    int counter=0;
    for (int i = 0; i < line.size(); i = i + 1) {
        char c = line.at((unsigned long) i);
        if (c!= ' '){
            if (counter==0)
                _command.push_back(c);
            else{
                _name.push_back(c);
            }
        }
        else{
            counter++;
        }
    }
}
