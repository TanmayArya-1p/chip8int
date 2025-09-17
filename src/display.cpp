#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include "../include/display.h"


#define WINDOW_NAME "Chip8"

chip8::Display::Display(int scale) {
    this->scale = scale;
    memset(this->pixels, 0, sizeof(this->pixels));
   	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}
    this->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED , scale*SCREEN_WIDTH, scale*SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!this->window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->winsurface = SDL_GetWindowSurface(this->window);
    if(!this->winsurface) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->clear();
}


chip8::Display::~Display() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void chip8::Display::clear() {
    SDL_FillRect(this->winsurface, NULL, SDL_MapRGB( this->winsurface->format, 0, 0, 0 ));
    memset(this->pixels, 0, sizeof(this->pixels));
    SDL_UpdateWindowSurface(this->window);
}

bool chip8::Display::draw_sprite(uint8_t x, uint8_t y, std::vector<uint8_t> sprite) {
    bool erased = false;
    for(size_t i=0;i<sprite.size();i++) {
        for(size_t j=0;j<8;j++) {
            if(sprite[i] & (0x80 >> j)) {

                int XX = (x+j)%SCREEN_WIDTH;
                int YY = (y+i)%SCREEN_HEIGHT;

                this->pixels[XX][YY] ^= true;
                SDL_Rect rect = {(int)((XX)*this->scale), (int)((YY)*this->scale), this->scale, this->scale};
                if(this->pixels[XX][YY]) {
                    SDL_FillRect(this->winsurface, &rect, SDL_MapRGB( this->winsurface->format, 255, 255, 255 ));
                } else {
                    erased = true;
                    SDL_FillRect(this->winsurface, &rect, SDL_MapRGB( this->winsurface->format, 0, 0, 0 ));
                }
            }
        }
    }
    SDL_UpdateWindowSurface(this->window);
    return erased;
}
