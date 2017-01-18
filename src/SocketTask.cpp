//
// Created by alonam on 1/17/17.
//

#include <string>
#include <connectionHandler.h>
#include <SocketTask.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/pthread/mutex.hpp>


using namespace std;

SocketTask::SocketTask(ConnectionHandler& c, boost::mutex* mutex) :
        handler(c), _mutex(mutex), bytes(), blockNumber(0), toSend(),upLoadfinished(false),
        sizeToSend(0),counterSend(0), packetSizeData(0), currentNumOfBlockACK(0),dataFile(){
}


//SocketTask::~SocketTask(){};

void SocketTask::run(){
    int i=1;
    while(i==1) {
//        bytes = {''};
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

int SocketTask:: handelWithAck(){
//    bytes={''};
    bool isACKBlockNumGet=handler.getBytes(bytes,2);
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
    }
    return 1;
}

void  SocketTask:: handelWithError(){
//    bytes={''};
    bool isErrorNum=handler.getBytes(bytes,2);
    string s("");
    bool isErrorMsg=handler.getFrameAscii(s,'0');
    if(isErrorNum && isErrorMsg){
        cout<< "Error" <<s.substr (0,s.length()-2)  << endl;;
    }
}

void SocketTask:: handelWithBCAST(){
//    bytes={''};
    bool isDelOrAddNum=handler.getBytes(bytes,1);
    string s("");
    bool isDelOrAddNumMsg=handler.getFrameAscii(s,'0');
    if(isDelOrAddNumMsg && isDelOrAddNum){
        short addDel=bytesToShort(bytes);
        if(addDel==0){
            cout<< "BCAST del" <<s.substr (0,s.length()-2) << endl;
        }
        else if(addDel==1){
            cout<< "BCAST add" <<s.substr (0,s.length()-2) << endl;
        }

    }
}

void SocketTask:: keepUploading(short currentBlock){
    if (currentBlock==1){
        FILE * file=fopen(handler.getFileUpload().c_str(),"rb");
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
        handler.setFileUpload("");
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
//        delete[] sending;
    }
}

void SocketTask::handelWithDATA() {
//    bytes={''};
    bool isPacketSize=handler.getBytes(bytes,2);
//    bytes={''};
    bool isBlockNum=handler.getBytes(bytes,2);
//    bytes={''};
    bool isDataGet=handler.getBytes(bytes,2);
    if((isBlockNum && isPacketSize) && isDataGet ){
        packetSizeData=bytesToShort(bytes);
        blockNumber=bytesToShort(bytes);
        if(blockNumber== currentNumOfBlockACK-1)
        if(handler.getLastSent()==6){
            if(blockNumber==1){
                dataFile=fopen("allTheFilesInServer.txt","ab");//TODO: check if this is currect
                counterSend=0;
            }
            keepHanderWithData();
        }else if(handler.getLastSent()==1){
            if(blockNumber){
                dataFile=fopen(handler.getFileDownload().c_str(),"ab");
                counterSend=0;
            }
            keepHanderWithData();
        }
    }
}

void SocketTask:: keepHanderWithData(){
    char addToFile[packetSizeData];
    for(int i=0;i<packetSizeData; i++){
        addToFile[i]=bytes[counterSend];
        counterSend++;
    }
    fwrite(addToFile,1, sizeof(addToFile),dataFile);
    ACK toSend(blockNumber);
    handler.sendPacketACK(toSend);
    if(handler.getLastSent()==1)
        cout<< "RRQ "<<handler.getFileDownload() << " " <<blockNumber<< endl;
//    delete [] addToFile;
    if(packetSizeData<512){
        if(handler.getLastSent()==1)
            cout<< "RRQ "<<handler.getFileDownload() << " complete" << endl;
        else{
            cout<< "Dirq "<<"allTheFilesInServer.txt" << " complete" << endl;
        }
        fclose(dataFile);
    }

}

//SocketTask::~SocketTask() {
//    delete handler;
//    delete _mutex;
//}


