# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build"

# Include any dependencies generated for this target.
include CMakeFiles/gserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gserver.dir/flags.make

CMakeFiles/gserver.dir/server.c.o: CMakeFiles/gserver.dir/flags.make
CMakeFiles/gserver.dir/server.c.o: ../server.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/gserver.dir/server.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/gserver.dir/server.c.o   -c "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/server.c"

CMakeFiles/gserver.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gserver.dir/server.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/server.c" > CMakeFiles/gserver.dir/server.c.i

CMakeFiles/gserver.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gserver.dir/server.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/server.c" -o CMakeFiles/gserver.dir/server.c.s

CMakeFiles/gserver.dir/server.c.o.requires:
.PHONY : CMakeFiles/gserver.dir/server.c.o.requires

CMakeFiles/gserver.dir/server.c.o.provides: CMakeFiles/gserver.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/gserver.dir/build.make CMakeFiles/gserver.dir/server.c.o.provides.build
.PHONY : CMakeFiles/gserver.dir/server.c.o.provides

CMakeFiles/gserver.dir/server.c.o.provides.build: CMakeFiles/gserver.dir/server.c.o

# Object files for target gserver
gserver_OBJECTS = \
"CMakeFiles/gserver.dir/server.c.o"

# External object files for target gserver
gserver_EXTERNAL_OBJECTS =

gserver: CMakeFiles/gserver.dir/server.c.o
gserver: CMakeFiles/gserver.dir/build.make
gserver: CMakeFiles/gserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable gserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gserver.dir/build: gserver
.PHONY : CMakeFiles/gserver.dir/build

CMakeFiles/gserver.dir/requires: CMakeFiles/gserver.dir/server.c.o.requires
.PHONY : CMakeFiles/gserver.dir/requires

CMakeFiles/gserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gserver.dir/clean

CMakeFiles/gserver.dir/depend:
	cd "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1" "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1" "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build" "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build" "/Users/kelvinrodriguez/Repos/Class_Work/CS460 Networks/CS460 Homework 1/build/CMakeFiles/gserver.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gserver.dir/depend

