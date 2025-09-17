#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include "display.h"
#include "memory.h"

namespace chip8 {

    struct registers {
        uint16_t pc;
        uint8_t sp;
        std::array<uint8_t, 16> v;
        uint16_t i;
        uint8_t delay_timer;
        uint8_t sound_timer;
    };

    class CPU {
        private:
            instruction::Instruction opcode;
            Memory* memory;
            Display* display;
        public:
            bool waiting_keypress;
            bool legacy_shift_mode;
            registers regs;
            std::vector<uint16_t> stack;

            CPU(Memory* memory, Display* display,bool legacy_shift_mode=false);
            void set_pc(uint16_t start);
            void reset();
            int next_instruction();
    };
}
