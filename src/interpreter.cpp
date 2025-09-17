#include <bits/stdc++.h>
#include <cstddef>
#include "../include/interpreter.h"


void chip8::CPU::set_pc(uint16_t start) {
    this->regs.pc = start;
}

void chip8::CPU::reset() {
    this->stack.clear();
    this->regs.sp = 0;
    this->regs.i = 0;
    this->regs.delay_timer = 0;
    this->regs.sound_timer = 0;
}


chip8::CPU::CPU(chip8::Memory* memory, chip8::Display* display) {
    this->memory = memory;
    this->display = display;
    this->reset();
    display->clear();
    memory->load_font();
}

int chip8::CPU::next_instruction() {
    this->opcode = memory->read_instruction(regs.pc);
    regs.pc += 2;

    switch(opcode.opnibble) {
        case(0x0):
            switch(opcode.opcode) {
                case(0x00E0):
                    display->clear();
                    break;
                case(0x00EE):
                    regs.pc = stack.back();
                    stack.pop_back();
                    break;
            }
            break;
        case(0x1): {
            uint16_t target = opcode.nnn;
            this->regs.pc = target;
            break;
        }
        case(0x6):
            this->regs.v[opcode.n1] = opcode.nn;
            break;
        case(0x7):
            this->regs.v[opcode.n1] += opcode.nn;
            break;
        case(0xA):
            this->regs.i = opcode.nnn;
            break;
        case(0xD): {
            size_t n = opcode.n3;
            std::vector<uint8_t> sprite(16,0);
            for (int i=0;i<n;i++) {
                sprite[i] = memory->read(this->regs.i+i);
            }
            display->draw_sprite(this->regs.v[opcode.n1], this->regs.v[opcode.n2], sprite);
            break;
        }
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode.opcode << std::endl;
            exit(1);
    }
    return opcode.opcode;
}
