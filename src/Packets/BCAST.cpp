//
// Created by alonam on 1/14/17.
//

#include "Packets/BCAST.h"

BCAST::BCAST(): opcode(9), deletedOrAdded(-1), fileName(""), lastByte('0') {}

BCAST::BCAST(char deletedOrAdded, string str): opcode(9), deletedOrAdded(deletedOrAdded), fileName(str), lastByte('0') {}

short BCAST::getOpcode() {
    return 9;
}

char BCAST::getDeletedOrAdded() {
    return deletedOrAdded;
}

void BCAST::setDeletedOrAdded(char deletedOrAdded) {
    this->deletedOrAdded=deletedOrAdded;
}

string BCAST::getFileName() {
    return fileName;
}

void BCAST::setFileName(string fileName) {
    this->fileName=fileName;
}
