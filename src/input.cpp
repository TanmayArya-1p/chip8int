#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <unordered_map>
#include "input.h"
#include "config.h"
#include <iostream>


bool chip8::handle_key_state_change(SDL_Event& event) {

    static std::unordered_map<SDL_Scancode , int> key_map = {
        {SDL_SCANCODE_1, 1},
        {SDL_SCANCODE_2, 2},
        {SDL_SCANCODE_3, 3},
        {SDL_SCANCODE_4, 0xC},
        {SDL_SCANCODE_Q, 4},
        {SDL_SCANCODE_W, 5},
        {SDL_SCANCODE_E, 6},
        {SDL_SCANCODE_R, 0xD},
        {SDL_SCANCODE_A, 7},
        {SDL_SCANCODE_S, 8},
        {SDL_SCANCODE_D, 9},
        {SDL_SCANCODE_F, 0xE},
        {SDL_SCANCODE_Z, 0xA},
        {SDL_SCANCODE_X, 0x0},
        {SDL_SCANCODE_C, 0xB},
        {SDL_SCANCODE_V, 0xF},
    };

    if(event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        return false;
    SDL_Scancode key = event.key.keysym.scancode;
    if(key_map.find(key) == key_map.end()) {
        return false;
    }
    chip8::KeyState[key_map[key]] = (event.type == SDL_KEYDOWN);

    #ifdef DEBUG_MODE
    std::cout << "Key state changed: " << key_map[key] << " to " << chip8::KeyState[key_map[key]] << std::endl;
    #endif


    return true;
}
