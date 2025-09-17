#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>
#include <bits/stdc++.h>


namespace chip8 {
    constexpr uint8_t SCREEN_HEIGHT = 32;
    constexpr uint8_t SCREEN_WIDTH = 64;
    class Display {
        SDL_Window* window;
        SDL_Surface* winsurface;
        bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
        int scale;
        public:
            Display(int scale);
            ~Display();
            bool draw_sprite(uint8_t x, uint8_t y, std::vector<uint8_t> sprite);
            void clear();
    };
}
