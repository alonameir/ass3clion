//
// Created by alonam on 1/17/17.
//

#include <string>
//#include <connectionHandler.h>
#include <SocketTask.h>

#include <boost/thread/pthread/mutex.hpp>


using namespace std;

SocketTask::SocketTask(ConnectionHandler& c, boost::mutex* mutex) :
        handler(c), _mutex(mutex), bytes(), blockNumber(0), toSend(),upLoadfinished(false),
        sizeToSend(0),counterSend(0), packetSizeData(0), currentNumOfBlockACK(-1),dataFile(), dirqData(""){
}


//SocketTask::~SocketTask(){};

void SocketTask::run(){
    int i=1;
    while(i==1) {
//        bytes = {''};
        cout  << "i'm in sockettask run()"<< endl;
        bool isOpcodeGet = handler.getBytes(bytes, 2);
        if (isOpcodeGet) {
            short opCode = bytesToShort(bytes);
            switch (opCode) {
                case 3: {
                    handelWithDATA();
                    break;
                }
                case 4: {
                   i= handelWithAck();
                    break;
                }
                case 5: {
                    handelWithError();
                    break;
                }
                case 9: {
                    handelWithBCAST();
                    break;
                }
            }
        }
    }
}

short  SocketTask:: bytesToShort(char* bytesArr)
{
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void  SocketTask:: shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void printArrA (const char * buffer, unsigned int bytesToRead) {
    for (int i = 0 ;i <bytesToRead ; ++i) {
        cout<< (int)buffer[i] << ",";
    }
    cout << std::endl;
}

int SocketTask:: handelWithAck(){
    cout<< "The OPCODE that was last sent is: " << handler.getLastSent() << endl;
    bool isACKBlockNumGet=handler.getBytes(bytes,2);
    printArrA(bytes, 2);
    if(isACKBlockNumGet){
        currentNumOfBlockACK=bytesToShort(bytes);
        cout<< "ACK " << currentNumOfBlockACK <<endl;
        if(currentNumOfBlockACK==0) {
            if(handler.getLastSent()==10){
                handler.close();
                cout<< "DISC " <<endl;
                handler.shouldTerminate=true;
                return 0;
            }
            else if(handler.getLastSent()==2 && !upLoadfinished){
                keepUploading(currentNumOfBlockACK);
            }
            return 1;
        }
        else if(currentNumOfBlockACK!=0 && blockNumber+1==currentNumOfBlockACK){
            if (handler.getLastSent()==2 && !upLoadfinished){
                keepUploading(currentNumOfBlockACK);
                return 1;
            }
            else if(upLoadfinished){
                blockNumber=0;
                return 1;
            }
        }
        else{
            ERROR tosend(8,"Invalid ACK");
            handler.sendPacketError(tosend);
            return 1;
        }
    }
    return 1;
}

void  SocketTask:: handelWithError(){
    bool isErrorNum=handler.getBytes(bytes,2);
    string s("");
    bool isErrorMsg=handler.getFrameAscii(s,'0');
    if(isErrorNum && isErrorMsg){
        cout<< "Error " <<s.substr (0,s.length()-1)  << endl;
    }
}

void SocketTask:: handelWithBCAST(){
    short addDel;
    bool isDelOrAddNum=handler.getBytes(bytes,1);
    if(isDelOrAddNum) {
        addDel=bytesToShort(bytes);
        string s("");
        bool isDelOrAddNumMsg=handler.getFrameAscii(s,0);
        if(isDelOrAddNumMsg){
            if(addDel==0){
                cout<< "BCAST del" <<s.substr (0,s.length()-2) << endl;
            }
            else if(addDel==1){
                cout<< "BCAST add" <<s.substr (0,s.length()-2) << endl;
            }
        }
    }
}

void SocketTask:: keepUploading(short currentBlock){
    if (currentBlock==0){
        FILE * file=fopen(handler.getFileUpload(),"rb");
        fseek (file , 0 , SEEK_END);
        sizeToSend=ftell(file);///tells the size of the file
        rewind(file);
        toSend=new char[sizeToSend];
        fread(toSend,1, sizeToSend, file);
        fclose(file);
    }
    if(sizeToSend-counterSend<512){
        char sending[sizeToSend-counterSend];
        int size= (int) (sizeToSend - counterSend);
        for(int i=0;i<size; i++){
            sending[i]=toSend[counterSend];
            counterSend++;
        }
        handler.sendData(size, sending, blockNumber);
        cout<< "RRQ "<<handler.getFileUpload() << " " <<blockNumber<< endl;
        cout<< "WRQ "<<handler.getFileUpload() << " complete"<< endl;
        handler.setFileUpload(nullptr);
        upLoadfinished=true;
        counterSend=0;
//        delete[] sending;
    }
    else{
        char sending[512];
        for(int i=0;i<512; i++){
            sending[i]=toSend[counterSend];
            counterSend++;
        }
        handler.sendData(512, sending, blockNumber);
        cout<< "RRQ "<<handler.getFileUpload() << " " <<blockNumber<< endl;
    }
}

void SocketTask::handelWithDATA() {
    bool isPacketSize = handler.getBytes(bytes, 2);
    if (isPacketSize)packetSizeData = bytesToShort(bytes);
    bool isBlockNum = handler.getBytes(bytes, 2);
    if (isBlockNum) blockNumber = bytesToShort(bytes);
    if (isBlockNum && isPacketSize) {
        bool isDataGet = handler.getBytes(bytes, (unsigned int) packetSizeData);
        if (isDataGet) {
            if (blockNumber == currentNumOfBlockACK - 1) {
                if (handler.getLastSent() == 6) {
                    if (blockNumber == 1) {
                        //dataFile = fopen("allTheFilesInServer.txt", "ab");//TODO: check if this is currect
                        counterSend = 0;
                    }
                    keepHanderWithData();
                } else if (handler.getLastSent() == 1) {
                    if (blockNumber) {
                        dataFile = fopen(handler.getFileDownload(), "ab");
                        counterSend = 0;
                    }
                    keepHanderWithData();
                }
            } else {
                ERROR tosend(8, "Invalid DATA");
                handler.sendPacketError(tosend);
            }
        }
    }
}

void SocketTask:: keepHanderWithData(){
    char addToFile[packetSizeData];
    for(int i=0;i<packetSizeData; i++){
        addToFile[i]=bytes[counterSend];
        counterSend++;
    }
    if (handler.getLastSent()==1)
        fwrite(addToFile,1, packetSizeData,dataFile);
    else{
        cout << "i'm before appand"<< endl;
        dirqData.append(addToFile);
    }
    ACK toSend(blockNumber);
    handler.sendPacketACK(toSend);
    if(packetSizeData<512){
        if(handler.getLastSent()==1)
            cout<< "RRQ "<<handler.getFileDownload() << " complete" << endl;
        else{
            printDirq();
        }
        fclose(dataFile);
    }

}

void SocketTask::printDirq() {
    int numOfFiles=1;
    string temp("");
    int i=0;
    while( i < dirqData.size()) {
        if (dirqData.at(i) == '\0') {
            cout << temp << " " << numOfFiles << endl;
            temp.clear();
            numOfFiles++;
        } else {
            char a = dirqData.at(i);
            temp.append(1, a);
            }
        i++;
    }

}



//SocketTask::~SocketTask() {
//    delete handler;
//    delete _mutex;
//}


