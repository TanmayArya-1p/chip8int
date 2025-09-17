#include "../include/display.h"
#include "../include/memory.h"
#include "../include/interpreter.h"

#include <unistd.h>


int main(int argc, char* argv[]) {
    chip8::Display* display = new chip8::Display(argv[2] ? atoi(argv[2]) : 20);
    chip8::Memory* memory = new chip8::Memory();

    memory->load_rom(argv[1]);

    chip8::CPU* cpu = new chip8::CPU(memory,display);
    cpu->set_pc(0x200);

    SDL_Event event;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(16);
        cpu->next_instruction();
    }

    return 0;
}
