#include "../include/display.h"
#include <unistd.h>


int main() {
    chip8::Display* x = new chip8::Display(10);
    x->draw_sprite(2, 2, {
        0xF0, 0x90, 0x90, 0x90, 0xF0,
    });

    SDL_Event event;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(16);
    }

    return 0;
}
