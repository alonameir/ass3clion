//
// Created by romybu on 14/01/17.
//

#include <boost/regex/config/cwchar.hpp>
#include <string>
#include <vector>

#ifndef ASS3CLION_PACKET_H
#define ASS3CLION_PACKET_H

using namespace std;

class Packet{
public:
    virtual short getOpcode()=0;
};

class PacketWithString: public Packet{
private:
    string s;
    char lastByte;

public:
    PacketWithString();
    PacketWithString(string str);
    string getString();
    ~PacketWithString();
    char getLastByte();
    virtual short getOpcode()=0;
    virtual void setString(string& str)=0;
};

class ACK: public Packet {

private:
    short opcode;
    short blockNumber;

public:
    ACK();
    ~ACK();
    ACK(short blockNumber);
    short getOpcode();
    short getBlockNumber();
    void setBlockNumber(short blockNumber);
};

class BCAST {
private:
    short opcode;
    char deletedOrAdded;
    string fileName;
    char lastByte;
public:
    BCAST();
    ~BCAST();
    BCAST(char deletedOrAdded, string str);
    short getOpcode();
    char getDeletedOrAdded();
    void setDeletedOrAdded(char deletedOrAdded);
    string getFileName();
    void setFileName(string fileName);
};

class DATA: public Packet{
private:
    short opcode;
    short packetSize;
    short blockNumber;
    int index;
    vector<char> data;

public:
//    DATA(short packetSize);
    DATA();
    ~DATA();
    short getOpcode();
    short getPacketSize();
    void setPacketSize(short ps);
    short getBlockNumber();
    void setBlockNumber(short blockNumber);
    vector<char> getData(); //TODO: CHECK IF WE NEED TO RETURN POINTER
    void addToData(char b);
};

class DELRQ : public PacketWithString {
private:
    short opcode;
public:
    DELRQ();
    //~DELRQ();
    DELRQ(string str);
    short getOpcode();
};

class DIRQ: public Packet{
private:
    short opcode;
public:
    DIRQ();
    ~DIRQ();
    short getOpcode();
};


class DISC: public Packet{
private:
    short opcode;
public:
    DISC();
    ~DISC();
    short getOpcode();
};


class ERROR: public Packet{
private:
    short opcode;
    short errorCode;
    string str;
    char byte;
public:
    ERROR();
    ~ERROR();
    short getOpcode();
    short getErrorcode();
    void setErrorcode(short errcode);
    string getStr();
    void setStr(string msg);
};


class LOGRQ: public PacketWithString {
private:
    short opcode;
public:
    LOGRQ();
    ~LOGRQ();
    LOGRQ(string str);
    short getOpcode();
};


class RRQ: public PacketWithString {
private:
    short opcode;
public:
    RRQ();
    ~RRQ();
    RRQ(string str);
    short getOpcode();
};

class WRQ: public PacketWithString {
private:
    short opcode;
public:
    WRQ();
    ~WRQ();
    WRQ(string str);
    short getOpcode();
};

#endif //ASS3CLION_PACKET_H
