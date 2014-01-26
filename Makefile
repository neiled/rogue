compile:
	clang++ -o gen/rogue src/**.cc -F/Library/Frameworks -framework SDL2
run: compile
	gen/rogue
