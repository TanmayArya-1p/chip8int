#include <array>
#include <cstdint>
#include <vector>
namespace chip8 {

    struct registers {
        uint16_t pc;
        uint8_t sp;
        std::array<uint8_t, 16> v;
        uint16_t i;
        uint8_t delay_timer;
        uint8_t sound_timer;
    };

    class Chip8VM {
        public:
            static registers regs;
            static std::vector<uint16_t> stack;



    }
}
