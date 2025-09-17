#include "../include/instruction.h"

chip8::instruction::Instruction chip8::instruction::decode(uint16_t opcode) {
    return Instruction{
        .opcode = opcode,
        .n1 = static_cast<uint8_t>((opcode >> 8) & 0xF),
        .n2 = static_cast<uint8_t>((opcode >> 4) & 0xF),
        .n3 = static_cast<uint8_t>(opcode & 0xF),

        .n = static_cast<uint16_t>(opcode & 0xF),
        .nn = static_cast<uint16_t>(opcode & 0xFF),
        .nnn = static_cast<uint16_t>(opcode & 0xFFF)
    };
}
