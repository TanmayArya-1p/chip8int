#pragma once
#include <SDL2/SDL_events.h>
#include <vector>
#include <array>

namespace chip8 {
    inline std::array<bool,16> KeyState;
    bool handle_key_state_change(SDL_Event& event);
}
