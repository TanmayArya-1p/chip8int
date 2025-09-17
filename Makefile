run:
	cmake -S . -B build
	cd build && make
	./build/chip8 ../roms/ibm.ch8

.PHONY: run
