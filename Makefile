compile:
	clang++ -std=c++11 -stdlib=libc++ -o rogue src/**.cc -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
run: compile
	rogue
