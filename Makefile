compile:
	clang++ -std=c++11 -stdlib=libc++ -o gen/rogue src/**.cc -F/Library/Frameworks -framework SDL2 -framework SDL2_image
run: compile
	gen/rogue
