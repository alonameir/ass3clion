//#include <Packets/Packet.h>
//#include <Packets/DIRQ.h>
//#include <Packets/DISC.h>
//#include <Packets/ACK.h>
#include "connectionHandler.h"

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
 
ConnectionHandler::ConnectionHandler(string host, short port):
        host_(host), port_(port), io_service_(), socket_(io_service_), fileUpload(""), fileDownload(""),
        lastSent(-1),shouldTerminate(false){}

ConnectionHandler::~ConnectionHandler() {
    close();
}

bool ConnectionHandler::connect() {
    std::cout << "Starting connect to "
              << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
            tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\n');
}

bool ConnectionHandler::sendLine(std::string& line) {
    return sendFrameAscii(line, '\n');
}

bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    // Stop when we encounter the null character. 
    // Notice that the null character is not appended to the frame string.
    try {
        do{
            getBytes(&ch, 1);
            frame.append(1, ch);
        }while (delimiter != ch);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
    bool result=sendBytes(frame.c_str(),frame.length());
    if(!result) return false;
    return sendBytes(&delimiter,1);
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

void shortToBytes(short num, char* bytesArr){
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ConnectionHandler:: sendPacket(PacketWithString& p){/** THIS METHOD SHOULD BE BLOCKING **/
    char* opcode;
    shortToBytes(p.getOpcode(),opcode);
    string frame=p.getString();
    bool firstSend=sendBytes(opcode,2);
    bool secondSend=sendFrameAscii(frame,'0');
    if (!firstSend || !secondSend){ } /** DO SOMETHING?? **/
}

void ConnectionHandler::sendPacketDIRQ() {
    char* opcode;
    shortToBytes(6,opcode);
    bool isSent=sendBytes(opcode,2);
    if (!isSent){} /** DO SOMETHING?? **/
}

void ConnectionHandler::sendPacketDISC() {
    char* opcode;
    shortToBytes(10,opcode);
    bool isSent=sendBytes(opcode,2);
    if (!isSent){} /** DO SOMETHING?? **/
}

void ConnectionHandler::sendPacketACK(ACK& p) {
    char* opcode;
    shortToBytes(4,opcode);
    char* blockNum;
    shortToBytes(p.getBlockNumber(),blockNum);
    sendBytes(opcode,2);
    sendBytes(blockNum,2);
    }


string &ConnectionHandler::getFileUpload()  {
    return fileUpload;
}

void ConnectionHandler::setFileUpload (string fileUpload) {
    ConnectionHandler::fileUpload = fileUpload;
}

string &ConnectionHandler::getFileDownload()  {
    return fileDownload;
}

void ConnectionHandler::setFileDownload( string &fileDownload) {
    ConnectionHandler::fileDownload = fileDownload;
}

void ConnectionHandler::sendData(int size,char buff[], short block) {///check where adding one to block number
    char twoBytes[2];//check if char*
    shortToBytes((short)3,twoBytes);//opCode send
    sendBytes(twoBytes,2);
    shortToBytes((short)size,twoBytes);//packetsize send
    sendBytes(twoBytes,2);
    shortToBytes(block+1,twoBytes);//block number send  ///!!!!!!!!!!!!!!!!!!!!!!
    sendBytes(twoBytes,2);
    sendBytes(buff,size);
//    delete[] twoBytes;
}

short ConnectionHandler::getLastSent()  {
    return lastSent;
}

void ConnectionHandler::setLastSent(short lastSent) {
    ConnectionHandler::lastSent = lastSent;
}

void ConnectionHandler::sendPacketData(ERROR &p) {
    char* opcode;
    shortToBytes(8,opcode);
    char* errorCode;
    shortToBytes(p.getErrorcode(),errorCode);
    sendBytes(opcode,2);
    sendBytes(errorCode,2);
    sendFrameAscii(p.getStr(), '0');
}

//ConnectionHandler::ConnectionHandler(): host_(), port_(),io_service_(), socket_(io_service_), fileUpload(), fileDownload(), lastSent() {}