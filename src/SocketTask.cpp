//
// Created by alonam on 1/17/17.
//

#include <string>
#include <connectionHandler.h>
#include <SocketTask.h>
using namespace std;

SocketTask::SocketTask(ConnectionHandler c) : handler(c), bytes(), bolckNumber(0) {}

~SocketTask();

void SocketTask::run(){
    while(1){
        bytes={''};
        bool isOpcodeGet=handler.getBytes(bytes,2);
        if(isOpcodeGet)
            short opCode=bytesToShort(bytes);
            switch(opCode){
                case 4:{
                    handelWithAck();
                }:
                case 5:{
                    handelWithError();
                }
                case 9:{
                    handelWithBCAST();
                }
            }
        else{
            //todo:send an error
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

void SocketTask:: handelWithAck(){
    bytes={''};
    bool isACKBlockNumGet=handler.getBytes(bytes,2);
    if(isACKBlockNumGet){
        short block=bytesToShort(bytes);
        if(block==0) {
            cout<< "ACK 0"  << endl;;
            if(handler.shouldTerminate())handler.close();
        }
        else if(block!=0 && blockNumber+1==block){
            if (block==1){
                if (handler.getFileUpload()!= nullptr){

                }
            }
        }
    }
}

void  SocketTask:: handelWithError(){
    bytes={''};
    bool isErrorNum=handler.getBytes(bytes,2);
    string s("");
    bool isErrorMsg=handler.getFrameAscii(s,'0');
    if(isErrorNum && isErrorMsg){
        cout<< "Error" <<s.substr (0,s.length()-2)  << endl;;
    }
}

void SocketTask:: handelWithBCAST(){
    bytes={''};
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

//
//size_t result;
//FILE* file=fopen("loston.mp3","rb");
//fseek (file , 0 , SEEK_END);
//long lSize = ftell (file);
//rewind (file);
//char* temp4=new char[lSize];
//result=fread(temp4,1,lSize,file);
//fclose(file);
//
//
//char towrite[lSize-2000];
//for (int i=0 ; i<lSize-2000; i++){
//towrite[i]=temp4[i];
//}
//cout<< sizeof(towrite)<<endl;
//FILE* file2=fopen("cd.mp3","ab");
//cout<< sizeof(char)<<endl;
//fwrite(towrite, 1, sizeof(towrite)-1 ,file2);
//char contread[2000];
//int counter=0;
//for (int i=lSize-2000;i<lSize;i++){
//contread[counter]=temp4[i];
//counter++;
//}
//fwrite(contread,1, sizeof(contread)-1,file2);
//fclose(file2);

