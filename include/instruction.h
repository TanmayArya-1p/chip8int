#include <bits/stdc++.h>
#include <cstdint>

namespace chip8 {
namespace instruction {

    struct Instruction {
        uint16_t opcode;

        uint8_t n1; //nibble 1
        uint8_t n2; //nibble 2
        uint8_t n3; //nibble 3

        uint16_t n;
        uint16_t nn;
        uint16_t nnn;
    };

    Instruction decode(uint16_t opcode);
} //namespace instruction
} //namespace chip8
