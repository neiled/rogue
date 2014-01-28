compile:
	clang++ -std=c++11 -stdlib=libc++ -o gen/rogue src/**.cc -F/Library/Frameworks -framework SDL2
run: compile
	gen/rogue
