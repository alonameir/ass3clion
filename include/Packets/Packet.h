//
// Created by romybu on 14/01/17.
//

#include <boost/regex/config/cwchar.hpp>
#include <string>

#ifndef ASS3CLION_PACKET_H
#define ASS3CLION_PACKET_H

#endif //ASS3CLION_PACKET_H
using namespace std;

class Packet{
public:
    virtual short getOpcode()=0;
    virtual void execute(BidiMessagingProtocolPacket& p)=0;
};

class PacketWithString: public Packet{
private:
    string s;
    char lastByte;

public:
    PacketWithString();
    PacketWithString(string str);
    string getString();

    char getLastByte();
    virtual short getOpcode()=0;
    virtual void execute(BidiMessagingProtocolPacket& p)=0;
    virtual void setString(string& str);

};

