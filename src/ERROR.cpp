//
// Created by alonam on 1/14/17.
//

#include <bits/basic_string.h>
#include <ERROR.h>
using namespace std;
ERROR::ERROR(): opcode(5), errorCode(-1), str(""), byte('0') {}

short ERROR::getOpcode() {
    return 5;
}

short ERROR::getErrorcode() {
    return errorCode;
}

void ERROR::setErrorcode(short errcode) {
    this->errorCode=errcode;
}

string ERROR::getStr() {
    return str;
}

void ERROR::setStr(string msg) {
    this->str=msg;
}
