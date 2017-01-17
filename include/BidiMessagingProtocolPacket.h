//
// Created by romybu on 14/01/17.
//

#ifndef ASS3CLION_BIDIMESSAGINGPROTOCOLPACKET_H
#define ASS3CLION_BIDIMESSAGINGPROTOCOLPACKET_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
using namespace std;

class BidiMessagingProtocolPacket {
private:
    string command;
    string fileName;

public:
    void readFromKeyboard(string line);
};


#endif //ASS3CLION_BIDIMESSAGINGPROTOCOLPACKET_H
