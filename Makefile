compile:
	clang++ -std=c++11 -stdlib=libc++ -o rogue src/**.cc -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
compile_linux:
	g++ -std=c++11 -o rogue src/**.cc -lSDL2 -lSDL2_image -lSDL2_ttf -I/usr/include
run: compile
	./rogue
