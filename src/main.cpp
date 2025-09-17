#include "../include/display.h"
#include "../include/memory.h"
#include "../include/interpreter.h"
#include "../include/input.h"


#include <SDL2/SDL_events.h>
#include <chrono>
#include <ctime>
#include <unistd.h>


constexpr double TIMER_REDUCTION_PERIOD = 1000.0/60;


int main(int argc, char* argv[]) {
    //chip8 <rom_file> <display_scale> <cycle_period>

    chip8::Display* display = new chip8::Display(argv[2] ? atoi(argv[2]) : 20);
    chip8::Memory* memory = new chip8::Memory();

    memory->load_rom(argv[1]);

    chip8::CPU* cpu = new chip8::CPU(memory,display);
    cpu->set_pc(0x200);

    SDL_Event event;
    bool quit = false;

    int ctr = 0;
    auto start_time = std::chrono::system_clock::now();

    auto timer_decrement_timer = start_time;

    while(!quit) {

        auto curr = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(curr - start_time);
        int reduce_timers = static_cast<int>(elapsed.count() / TIMER_REDUCTION_PERIOD);
        cpu->regs.delay_timer = cpu->regs.delay_timer > reduce_timers ? cpu->regs.delay_timer - reduce_timers : 0;
        cpu->regs.sound_timer = cpu->regs.sound_timer > reduce_timers ? cpu->regs.sound_timer - reduce_timers : 0;
        timer_decrement_timer = std::chrono::system_clock::now();


        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            } else {
                if(chip8::handle_key_state_change(event) && cpu->waiting_keypress) {
                    cpu->waiting_keypress = false;
                    cpu->regs.pc+=2;
                }
            }
        }
        SDL_Delay(argv[3] ? atoi(argv[3]) : 30);
        ctr++;
        cpu->next_instruction();
    }

    auto end_time = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Execution time: " << duration << " ms" << std::endl;
    std::cout << "Instructions per second: " << ctr/(duration/1000.0) << std::endl;
    return 0;
}
