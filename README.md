## Chip8 Emulator

This Project completely implements the Chip8 instruction set with some support for legacy behaviour.

To build just run `make build` in the root directory.


### Usage

```bash
chip8 <rom_file> <display_scale> <clock_period>
```

A clock period of `20 ms` usually works well with most ROMs but some ROMs might require a much lower cycle period.

For legacy behaviour support you need to enable the required flags in [config.h](https://github.com/TanmayArya-1p/chip8int/blob/master/include/config.h) and build independently.

Check out [this](https://johnearnest.github.io/chip8Archive/) repository of chip8 ROMs to try out.
