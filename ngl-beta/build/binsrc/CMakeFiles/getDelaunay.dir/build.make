# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.12.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.12.1/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/neiled/dev/cpp/rogue/ngl-beta

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/neiled/dev/cpp/rogue/ngl-beta/build

# Include any dependencies generated for this target.
include binsrc/CMakeFiles/getDelaunay.dir/depend.make

# Include the progress variables for this target.
include binsrc/CMakeFiles/getDelaunay.dir/progress.make

# Include the compile flags for this target's objects.
include binsrc/CMakeFiles/getDelaunay.dir/flags.make

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o: binsrc/CMakeFiles/getDelaunay.dir/flags.make
binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o: ../binsrc/getDelaunay.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/neiled/dev/cpp/rogue/ngl-beta/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o"
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o -c /Users/neiled/dev/cpp/rogue/ngl-beta/binsrc/getDelaunay.cpp

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/getDelaunay.dir/getDelaunay.cpp.i"
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/neiled/dev/cpp/rogue/ngl-beta/binsrc/getDelaunay.cpp > CMakeFiles/getDelaunay.dir/getDelaunay.cpp.i

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/getDelaunay.dir/getDelaunay.cpp.s"
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/neiled/dev/cpp/rogue/ngl-beta/binsrc/getDelaunay.cpp -o CMakeFiles/getDelaunay.dir/getDelaunay.cpp.s

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.requires:
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.requires

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.provides: binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.requires
	$(MAKE) -f binsrc/CMakeFiles/getDelaunay.dir/build.make binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.provides.build
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.provides

binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.provides.build: binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o

# Object files for target getDelaunay
getDelaunay_OBJECTS = \
"CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o"

# External object files for target getDelaunay
getDelaunay_EXTERNAL_OBJECTS =

binsrc/getDelaunay: binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o
binsrc/getDelaunay: binsrc/CMakeFiles/getDelaunay.dir/build.make
binsrc/getDelaunay: binsrc/CMakeFiles/getDelaunay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable getDelaunay"
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/getDelaunay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
binsrc/CMakeFiles/getDelaunay.dir/build: binsrc/getDelaunay
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/build

binsrc/CMakeFiles/getDelaunay.dir/requires: binsrc/CMakeFiles/getDelaunay.dir/getDelaunay.cpp.o.requires
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/requires

binsrc/CMakeFiles/getDelaunay.dir/clean:
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc && $(CMAKE_COMMAND) -P CMakeFiles/getDelaunay.dir/cmake_clean.cmake
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/clean

binsrc/CMakeFiles/getDelaunay.dir/depend:
	cd /Users/neiled/dev/cpp/rogue/ngl-beta/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/neiled/dev/cpp/rogue/ngl-beta /Users/neiled/dev/cpp/rogue/ngl-beta/binsrc /Users/neiled/dev/cpp/rogue/ngl-beta/build /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc /Users/neiled/dev/cpp/rogue/ngl-beta/build/binsrc/CMakeFiles/getDelaunay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : binsrc/CMakeFiles/getDelaunay.dir/depend

