#include "../include/memory.h"
#include <stdexcept>

void chip8::Memory::clear() {
    buffer.fill(0);
    load_font();
}

chip8::Memory::Memory() {
    this->clear();
    this->load_font();
}

uint8_t chip8::Memory::read(uint16_t address) {
    if(address>=MEMORY_SIZE) throw std::out_of_range("Invalid Address");
    return (buffer[address]);
}

void chip8::Memory::write(uint16_t address, uint8_t value) {
    if(address>=MEMORY_SIZE) throw std::out_of_range("Invalid Address");
    buffer[address] = value;
}


void chip8::Memory::write_word(word content, word address) {
    if(address >= MEMORY_SIZE-1) throw std::out_of_range("Invalid Address");
    buffer[address] = content >> 8;
    buffer[address+1] = content & 0xFF;
}

word chip8::Memory::read_word(word address) {
    return buffer[address] << 8 | buffer[address+1];
}


void chip8::Memory::load_font() {
    for(int i=0x050; i<0x09F; i++) {
        buffer[i] = chip8_fontset[i-0x050];
    }
}
