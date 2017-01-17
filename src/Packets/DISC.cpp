//
// Created by alonam on 1/14/17.
//

#include <Packets/DISC.h>
#include "Packets/Packet.h"

using namespace std;


short DISC::getOpcode() {
    return 10;
}

DISC::DISC() : opcode(10) {}

DISC::~DISC() {

}
