#include <bits/stdc++.h>
#include <cstddef>
#include "../include/interpreter.h"
#include "../include/input.h"


#define LEGACY_SHIFT_MODE 0
#define LEGACY_JUMP_OFFSET 0
#define AMIGA_OVERFLOW_FLAGSET 1

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


chip8::CPU::CPU(chip8::Memory* memory, chip8::Display* display, bool legacy_shift_mode) {
    this->memory = memory;
    this->display = display;
    this->legacy_shift_mode = legacy_shift_mode;
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
                    //clear display
                    display->clear();
                    break;
                case(0x00EE):
                    //return after subroutine call
                    regs.pc = stack.back();
                    stack.pop_back();
                    break;
            }
            break;
        case(0x1): {
            //jump
            uint16_t target = opcode.nnn;
            this->regs.pc = target;
            break;
        }
        case(0x2): {
            //jump and link
            uint16_t target = opcode.nnn;
            stack.push_back(regs.pc);
            this->regs.pc = target;
            break;
        }
        case(0x3): {
            //skip if equal
            if(this->regs.v[opcode.n1] == opcode.nn)
                this->regs.pc += 2;
            break;
        }
        case(0x4): {
            //skip if not equal
            if(this->regs.v[opcode.n1] != opcode.nn)
                this->regs.pc += 2;
            break;
        }
        case(0x5) : {
            //skip if 2 register values are equation
            if(this->regs.v[opcode.n1] == this->regs.v[opcode.n2])
                this->regs.pc += 2;
            break;
        }
        case(0x6):
            //set register
            this->regs.v[opcode.n1] = opcode.nn;
            break;
        case(0x7):
            //add to register
            this->regs.v[opcode.n1] += opcode.nn;
            break;
        case(0x8): {
            //arithmetic and logical
            switch(opcode.n3) {
                case(0x0):
                    //vx=vy
                    this->regs.v[opcode.n1] = this->regs.v[opcode.n2];
                    break;
                case(0x1):
                    //vx=vx|vy
                    this->regs.v[opcode.n1] = this->regs.v[opcode.n2] | this->regs.v[opcode.n1];
                    break;
                case(0x2):
                    //vx=vx&vy
                    this->regs.v[opcode.n1] = this->regs.v[opcode.n2] & this->regs.v[opcode.n1];
                    break;
                case(0x3):
                    //vx=vx^vy
                    this->regs.v[opcode.n1] = this->regs.v[opcode.n2] ^ this->regs.v[opcode.n1];
                    break;
                case(0x4):
                    //vx=vx+vy
                    this->regs.v[opcode.n1] += this->regs.v[opcode.n2];
                    break;
                case(0x5):
                    //vx=vx-vy
                    this->regs.v[opcode.n1] -= this->regs.v[opcode.n2];
                    break;
                case(0x6):
                    //vx=vx>>1
                    if(this->legacy_shift_mode || LEGACY_SHIFT_MODE)
                        this->regs.v[opcode.n1] = this->regs.v[opcode.n2];
                    this->regs.v[0xF] = this->regs.v[opcode.n1] & 1;
                    this->regs.v[opcode.n1] >>= 1;
                    break;
                case(0x7):
                    //vx=vy-vx
                    this->regs.v[opcode.n1] = this->regs.v[opcode.n2] - this->regs.v[opcode.n1];
                    break;
                case(0xE):
                    //vx=vx<<1
                    if(this->legacy_shift_mode || LEGACY_SHIFT_MODE)
                        this->regs.v[opcode.n1] = this->regs.v[opcode.n2];
                    this->regs.v[0xF] = this->regs.v[opcode.n1] >> 7;
                    this->regs.v[opcode.n1] <<= 1;
                    break;
            }
            break;
        }
        case(0x9):
            //skip if 2 register values are not equal
            if(this->regs.v[opcode.n1] != this->regs.v[opcode.n2])
                this->regs.pc += 2;
            break;
        case(0xA):
            //set index register
            this->regs.i = opcode.nnn;
            break;
        case(0xB):
            //jump with offset
            this->regs.pc = opcode.nnn + this->regs.v[LEGACY_JUMP_OFFSET ? 0 : opcode.n1];
            break;
        case(0xC):
            //random number CXNN
            this->regs.v[opcode.n1] = (rand() % 256) & opcode.nn;
            break;
        case(0xD): {
            //draw sprite
            size_t n = opcode.n3;
            std::vector<uint8_t> sprite(16,0);
            for (int i=0;i<n;i++) {
                sprite[i] = memory->read(this->regs.i+i);
            }
            display->draw_sprite(this->regs.v[opcode.n1], this->regs.v[opcode.n2], sprite);
            break;
        }
        case(0xE) : {
            //conditionals based on key state
            switch (opcode.nn) {
                case(0x9E):
                    //skip if key is pressed
                    if(chip8::KeyState.at(this->regs.v[opcode.n1]))
                        this->regs.pc += 2;
                    break;
                case(0xA1):
                    //skip if key is not pressed
                    if(!chip8::KeyState.at(this->regs.v[opcode.n1]))
                        this->regs.pc += 2;
                    break;
                default:
                    std::cerr << "Unknown opcode: " << std::hex << opcode.opcode << std::endl;
                    exit(1);
            }
            break;
        }
        case(0xF) : {
            switch(opcode.nn) {
                case(0x1E) : {

                    #ifdef AMIGA_OVERFLOW_FLAGSET
                        if(static_cast<int>(this->regs.i) + static_cast<int>(this->regs.v[opcode.n1]) > 0xFF)
                            this->regs.v[0xF] = 1;
                        else
                            this->regs.v[0xF] = 0;
                    #endif

                    this->regs.i += this->regs.v[opcode.n1];
                    break;
                }
                case(0x0A) : {
                    //wait for keypress
                    this->waiting_keypress = true;
                    this->regs.pc-=2;
                    break;
                }
                case(0x29) : {
                    //set i to address of requested font
                    this->regs.i = 0x050+this->regs.v[opcode.n1];
                    break;
                }
                case(0x33): {
                    //binary to decimal conversion
                    uint8_t x = this->regs.v[opcode.n1];
                    this->memory->write(this->regs.i, x%10);
                    x /= 10;
                    this->memory->write(this->regs.i+1, x%10);
                    x /= 10;
                    this->memory->write(this->regs.i+2, x%10);
                    break;
                }
                case(0x55): {
                    //store registers v0-vX in memory starting at i
                    for(uint8_t i = 0; i <= opcode.n1; i++)
                        this->memory->write(this->regs.i+i, this->regs.v[i]);
                    break;
                }
                case(0x65): {
                    //load registers v0-vX from memory starting at i
                    for(uint8_t i = 0; i <= opcode.n1; i++)
                        this->regs.v[i] = this->memory->read(this->regs.i+i);
                    break;
                }
            }
            break;
        }
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode.opcode << std::endl;
            exit(1);
    }
    return opcode.opcode;
}
