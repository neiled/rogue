# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = "/Applications/CMake 2.8-1.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-1.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-1.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cdcorrea/Research/ngl/qhull

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cdcorrea/Research/ngl/qhull/build

# Include any dependencies generated for this target.
include CMakeFiles/qhull.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/qhull.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qhull.dir/flags.make

CMakeFiles/qhull.dir/src/qhull/unix.c.o: CMakeFiles/qhull.dir/flags.make
CMakeFiles/qhull.dir/src/qhull/unix.c.o: ../src/qhull/unix.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/cdcorrea/Research/ngl/qhull/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/qhull.dir/src/qhull/unix.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/qhull.dir/src/qhull/unix.c.o   -c /Users/cdcorrea/Research/ngl/qhull/src/qhull/unix.c

CMakeFiles/qhull.dir/src/qhull/unix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qhull.dir/src/qhull/unix.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/cdcorrea/Research/ngl/qhull/src/qhull/unix.c > CMakeFiles/qhull.dir/src/qhull/unix.c.i

CMakeFiles/qhull.dir/src/qhull/unix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qhull.dir/src/qhull/unix.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/cdcorrea/Research/ngl/qhull/src/qhull/unix.c -o CMakeFiles/qhull.dir/src/qhull/unix.c.s

CMakeFiles/qhull.dir/src/qhull/unix.c.o.requires:
.PHONY : CMakeFiles/qhull.dir/src/qhull/unix.c.o.requires

CMakeFiles/qhull.dir/src/qhull/unix.c.o.provides: CMakeFiles/qhull.dir/src/qhull/unix.c.o.requires
	$(MAKE) -f CMakeFiles/qhull.dir/build.make CMakeFiles/qhull.dir/src/qhull/unix.c.o.provides.build
.PHONY : CMakeFiles/qhull.dir/src/qhull/unix.c.o.provides

CMakeFiles/qhull.dir/src/qhull/unix.c.o.provides.build: CMakeFiles/qhull.dir/src/qhull/unix.c.o
.PHONY : CMakeFiles/qhull.dir/src/qhull/unix.c.o.provides.build

# Object files for target qhull
qhull_OBJECTS = \
"CMakeFiles/qhull.dir/src/qhull/unix.c.o"

# External object files for target qhull
qhull_EXTERNAL_OBJECTS =

qhull: CMakeFiles/qhull.dir/src/qhull/unix.c.o
qhull: libqhullstatic.a
qhull: CMakeFiles/qhull.dir/build.make
qhull: CMakeFiles/qhull.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable qhull"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qhull.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qhull.dir/build: qhull
.PHONY : CMakeFiles/qhull.dir/build

CMakeFiles/qhull.dir/requires: CMakeFiles/qhull.dir/src/qhull/unix.c.o.requires
.PHONY : CMakeFiles/qhull.dir/requires

CMakeFiles/qhull.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qhull.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qhull.dir/clean

CMakeFiles/qhull.dir/depend:
	cd /Users/cdcorrea/Research/ngl/qhull/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cdcorrea/Research/ngl/qhull /Users/cdcorrea/Research/ngl/qhull /Users/cdcorrea/Research/ngl/qhull/build /Users/cdcorrea/Research/ngl/qhull/build /Users/cdcorrea/Research/ngl/qhull/build/CMakeFiles/qhull.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qhull.dir/depend

