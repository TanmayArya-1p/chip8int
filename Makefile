run:
	cmake -S . -B build
	cd build && make
	./build/chip8

.PHONY: run
