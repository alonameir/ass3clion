#pragma once

#include "MessageEncoderDecoder.h"
#include <string>
#include <vector>

namespace bgu
{
    namespace spl171
    {
        namespace net
        {
            namespace api
            {

                using bgu::spl171::net::api::bidi::Packets::Packet;
                using namespace bgu::spl171::net::api::bidi::Packets;



                class MessageEncoderDecoderImp : public MessageEncoderDecoder<Packet*>
                {
                private:
                    int counter = 0;
                    //private int countAck=0;
                public:
                    std::vector<char> start(2);
                    short opcode = -1;
                    bool isStarted = false;
                    Packet *toReturn;
                private:
                    std::vector<char> bytes(1 << 10); //start with 1k
                    int len = 0;
                    AtomicInteger *loaded = new AtomicInteger();


                public:
                    virtual ~MessageEncoderDecoderImp()
                    {
                        delete toReturn;
                        delete loaded;
                    }

                    virtual Packet *decodeNextByte(char nextByte);

                    virtual std::vector<char> encode(Packet *message);

                private:
                    Packet *buildDATA(char nextByte);

                    Packet *buildRRQ(char nextByte);

                    Packet *buildWRQ(char nextByte);

                    Packet *buildACK(char nextByte);

                    Packet *buildERROR(char nextByte);

                    Packet *buildLOGRQ(char nextByte);

                    Packet *buildDELRQ(char nextByte);

                    Packet *buildBCAST(char nextByte);


                    std::vector<char> createBytesArrayWithString(PacketsWithString *p);

                public:
                    virtual short bytesToShort(std::vector<char> &byteArr);

                    virtual std::vector<char> shortToBytes(short num);

                private:
                    void pushByte(char nextByte);

                    std::wstring popString();

                    std::vector<char> mergeArrays(std::vector<char> &tmp1, std::vector<char> &tmp2);

                };


            }
        }
    }
}
