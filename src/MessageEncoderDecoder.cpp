#include "MessageEncoderDecoderImp.h"

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

                Packet *MessageEncoderDecoderImp::decodeNextByte(char nextByte)
                {
                    if (counter < 2)
                    {
                        start[counter] = nextByte;
                        counter++;
                    }
                    if (counter == 2)
                    {
                        opcode = bytesToShort(start);
                        counter++;
                        if (opcode == 6)
                        {
                            return new DIRO();
                        }
                        else if (opcode == 10)
                        {
                            return new DISC();
                        }
                        return nullptr;
                    }
                    if (opcode != -1 && counter >= 3)
                    {
                        if (opcode < 1 || opcode>10)
                        {
                            return new ERROR(static_cast<short>(4), L"Illegal TFTP operation – Unknown Opcode");
                        }
                        switch (opcode)
                        {
                            case 1:
                            {
                                return buildRRQ(nextByte);
                            }
                            case 2:
                            {
                                return buildWRQ(nextByte);
                            }
                            case 3:
                            {
                                return buildDATA(nextByte);
                            }
                            case 4:
                            {
                                return buildACK(nextByte);
                            }
                            case 5:
                            {
                                return buildERROR(nextByte);
                            }
                            case 7:
                            {
                                return buildLOGRQ(nextByte);
                            }
                            case 8:
                            {
                                return buildDELRQ(nextByte);
                            }
                            case (9):
                            {
                                return buildBCAST(nextByte);
                            }
                        }
                    }
                    return nullptr;
                }

                std::vector<char> MessageEncoderDecoderImp::encode(Packet *message)
                {
                    switch (message->getOpcode())
                    {
                        case 1:
                        {
                            return createBytesArrayWithString(static_cast<PacketsWithString*>(message));
                        }
                        case 2:
                        {
                            return createBytesArrayWithString(static_cast<PacketsWithString*>(message));
                        }
                        case 3:
                        {
                            std::vector<char> tmp = shortToBytes((message)->getOpcode());
                            std::vector<char> tmp2 = shortToBytes((static_cast<DATA*>(message))->getPacketSize());
                            std::vector<char> midAns = mergeArrays(tmp, tmp2);
                            std::vector<char> tmp3 = shortToBytes((static_cast<DATA*>(message))->getBlockNumber());
                            std::vector<char> midAns2 = mergeArrays(midAns, tmp3);

                            return mergeArrays(midAns2, (static_cast<DATA*>(message))->getData());
                        }
                        case 4:
                        {
                            std::vector<char> tmp = shortToBytes((message)->getOpcode());
                            std::vector<char> tmp2 = shortToBytes((static_cast<ACK*>(message))->getBlockNumber());
                            return mergeArrays(tmp, tmp2);
                        }
                        case 5:
                        {
                            std::vector<char> tmp = shortToBytes((message)->getOpcode());
                            std::vector<char> tmp2 = shortToBytes((static_cast<ERROR*>(message))->getErrorCode());
                            std::vector<char> midAns = mergeArrays(tmp, tmp2);
                            std::vector<char> tmp3 = ((static_cast<ERROR*>(message))->getErrMsg() + std::wstring(L"0")).getBytes();
                            return mergeArrays(midAns, tmp3);
                        }
                        case 6:
                        {
                            return shortToBytes((message)->getOpcode());
                        }
                        case 7:
                        {
                            return createBytesArrayWithString(static_cast<PacketsWithString*>(message));
                        }
                        case 8:
                        {
                            return createBytesArrayWithString(static_cast<PacketsWithString*>(message));
                        }
                        case 9:
                        {
                            std::vector<char> tmp = shortToBytes((message)->getOpcode());
                            std::vector<char> tmp2 = shortToBytes((static_cast<BCAST*>(message))->getDeletedOrAdded());
                            std::vector<char> midAns = mergeArrays(tmp, tmp2);
                            std::vector<char> tmp3 = ((static_cast<BCAST*>(message))->getFileName() + std::wstring(L"0")).getBytes();
                            return mergeArrays(midAns, tmp3);
                        }
                        case 10:
                        {
                            return shortToBytes((message)->getOpcode());
                        }
                    }
                    return nullptr;
                }

                Packet *MessageEncoderDecoderImp::buildDATA(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new DATA();
                        isStarted = true;
                        counter = 10;
                    }
                    if (counter < 12)
                    {
                        start[counter - 10] = nextByte;
                        counter++;
                    }
                    if (counter == 12)
                    {
                        (static_cast<DATA*>(toReturn))->setPacketSize(bytesToShort(start));
                        (static_cast<DATA*>(toReturn))->initDataArray((static_cast<DATA*>(toReturn))->getPacketSize());
                        counter++;
                        return nullptr;
                    }
                    if (counter == 13)
                    {
                        start[0] = nextByte;
                        counter++;
                        return nullptr;
                    }
                    if (counter == 14)
                    {
                        start[1] = nextByte;
                        (static_cast<DATA*>(toReturn))->setBlockNumber(bytesToShort(start));
                        counter++;
                        return nullptr;
                    }
                    if (counter > 14 && loaded->get() < (static_cast<DATA*>(toReturn))->getPacketSize())
                    {
                        (static_cast<DATA*>(toReturn))->addToData(nextByte);
                        loaded->incrementAndGet();
                    }
                    if (counter > 14 && loaded->get() == (static_cast<DATA*>(toReturn))->getPacketSize())
                    {
                        return toReturn;
                    }

                    return nullptr;
                }

                Packet *MessageEncoderDecoderImp::buildRRQ(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new RRQ();
                        isStarted = true;
                    }

                    if (nextByte == 0)
                    {
                        (static_cast<RRQ*>(toReturn))->setString(popString());
                        return toReturn;
                    }

                    pushByte(nextByte);
                    return nullptr;

                }

                Packet *MessageEncoderDecoderImp::buildWRQ(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new WRQ();
                        isStarted = true;
                    }

                    if (nextByte == 0)
                    {
                        (static_cast<WRQ*>(toReturn))->setString(popString());
                        return toReturn;
                    }

                    pushByte(nextByte);
                    return nullptr;

                }

                Packet *MessageEncoderDecoderImp::buildACK(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new ACK();
                        isStarted = true;
                        counter = 10;
                    }

                    if (counter < 12)
                    {
                        start[counter - 10] = nextByte;
                        counter++;
                    }

                    if (counter == 12)
                    {
                        (static_cast<ACK*>(toReturn))->setBlockNumber(bytesToShort(start));
                        return toReturn;
                    }

                    return nullptr;

                }

                Packet *MessageEncoderDecoderImp::buildERROR(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new ERROR();
                        isStarted = true;
                        counter = 10;
                    }
                    if (counter < 12)
                    {
                        start[counter - 10] = nextByte;
                        counter++;
                    }

                    if (counter == 12)
                    {
                        (static_cast<ERROR*>(toReturn))->setErrorCode(bytesToShort(start));
                        counter++;
                        return nullptr;
                    }

                    if (counter > 12)
                    {
                        if (nextByte == 0)
                        {
                            (static_cast<ERROR*>(toReturn))->setErrMsg(popString());
                            return toReturn;
                        }

                        pushByte(nextByte);
                    }

                    return nullptr;

                }

                Packet *MessageEncoderDecoderImp::buildLOGRQ(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new LOGRQ();
                        isStarted = true;
                    }

                    if (nextByte == 0)
                    {
                        (static_cast<LOGRQ*>(toReturn))->setString(popString());
                        return toReturn;
                    }

                    pushByte(nextByte);
                    return nullptr;
                }

                Packet *MessageEncoderDecoderImp::buildDELRQ(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new DELRQ();
                        isStarted = true;
                    }

                    if (nextByte == 0)
                    {
                        (static_cast<DELRQ*>(toReturn))->setString(popString());
                        return toReturn;
                    }

                    pushByte(nextByte);
                    return nullptr;
                }

                Packet *MessageEncoderDecoderImp::buildBCAST(char nextByte)
                {
                    if (!isStarted)
                    {
                        toReturn = new BCAST();
                        isStarted = true;
                        (static_cast<BCAST*>(toReturn))->setDeletedOrAdded(nextByte);
                    }

                    else
                    {
                        if (nextByte == 0)
                        {
                            (static_cast<BCAST*>(toReturn))->setFileName(popString());
                            return toReturn;
                        }

                        pushByte(nextByte);
                    }

                    return nullptr;
                }

                std::vector<char> MessageEncoderDecoderImp::createBytesArrayWithString(PacketsWithString *p)
                {
                    std::vector<char> tmp = shortToBytes((p)->getOpcode());
                    std::vector<char> tmp2 = (p->getString() + std::wstring(L"0")).getBytes();
                    return mergeArrays(tmp, tmp2);
                }

                short MessageEncoderDecoderImp::bytesToShort(std::vector<char> &byteArr)
                {
                    short result = static_cast<short>((byteArr[0] & 0xff) << 8);
                    result += static_cast<short>(byteArr[1] & 0xff);
                    return result;
                }

                std::vector<char> MessageEncoderDecoderImp::shortToBytes(short num)
                {
                    std::vector<char> bytesArr(2);
                    bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
                    bytesArr[1] = static_cast<char>(num & 0xFF);
                    return bytesArr;
                }

                void MessageEncoderDecoderImp::pushByte(char nextByte)
                {
                    if (len >= bytes.size())
                    {
                        bytes = Arrays::copyOf(bytes, len * 2);
                    }

                    bytes[len++] = nextByte;
                }

                std::wstring MessageEncoderDecoderImp::popString()
                {
                    std::wstring result = std::wstring(bytes, 0, len, StandardCharsets::UTF_8);
                    len = 0;
                    return result;
                }

                std::vector<char> MessageEncoderDecoderImp::mergeArrays(std::vector<char> &tmp1, std::vector<char> &tmp2)
                {
                    std::vector<char> ans(tmp1.size() + tmp2.size());
                    int i = 0;
                    for (int j = 0; j < tmp1.size(); j++)
                    {
                        ans[i] = tmp1[j];
                        i++;
                    }
                    for (int j = 0; j < tmp2.size(); j++)
                    {
                        ans[i] = tmp2[j];
                        i++;
                    }
                    return ans;
                }
            }
        }
    }
}
