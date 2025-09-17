#include "../include/memory.h"
#include <fstream>
#include <stdexcept>

std::array<uint8_t, chip8::MEMORY_SIZE> chip8::Memory::buffer;

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

chip8::instruction::Instruction chip8::Memory::read_instruction(word pc) {
    return chip8::instruction::decode(read_word(pc));
}

void chip8::Memory::load_rom(const std::string &path) {
    std::ifstream rom(path, std::ios::binary);
    if(!rom.is_open()) throw std::runtime_error("Failed to open ROM file");

    rom.seekg(0, std::ios::end);
    size_t size = rom.tellg();
    rom.seekg(0, std::ios::beg);

    if(size > (MEMORY_SIZE - 0x200)) throw std::runtime_error("ROM file too large");
    rom.read(reinterpret_cast<char*>(buffer.data() + 0x050), size);
    rom.close();
}
