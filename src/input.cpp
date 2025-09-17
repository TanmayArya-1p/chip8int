#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <unordered_map>
#include "../include/input.h"


bool chip8::handle_key_state_change(SDL_Event& event) {

    static std::unordered_map<SDL_Scancode , int> key_map = {
        {SDL_SCANCODE_1, 0},
        {SDL_SCANCODE_2, 1},
        {SDL_SCANCODE_3, 2},
        {SDL_SCANCODE_4, 12},
        {SDL_SCANCODE_Q, 3},
        {SDL_SCANCODE_W, 4},
        {SDL_SCANCODE_E, 5},
        {SDL_SCANCODE_R, 13},
        {SDL_SCANCODE_A, 6},
        {SDL_SCANCODE_S, 7},
        {SDL_SCANCODE_D, 8},
        {SDL_SCANCODE_F, 14},
        {SDL_SCANCODE_Z, 9},
        {SDL_SCANCODE_X, 10},
        {SDL_SCANCODE_C, 11},
        {SDL_SCANCODE_V, 15},
    };

    if(event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        return false;
    SDL_Scancode key = event.key.keysym.scancode;
    if(key_map.find(key) == key_map.end()) {
        return false;
    }
    chip8::KeyState[key_map[key]] = (event.type == SDL_KEYDOWN);
    return true;
}
