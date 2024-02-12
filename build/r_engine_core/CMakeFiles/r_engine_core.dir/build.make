# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/richstog/Documents/projects/r_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/richstog/Documents/projects/r_engine/build

# Include any dependencies generated for this target.
include r_engine_core/CMakeFiles/r_engine_core.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include r_engine_core/CMakeFiles/r_engine_core.dir/compiler_depend.make

# Include the progress variables for this target.
include r_engine_core/CMakeFiles/r_engine_core.dir/progress.make

# Include the compile flags for this target's objects.
include r_engine_core/CMakeFiles/r_engine_core.dir/flags.make

r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o: r_engine_core/CMakeFiles/r_engine_core.dir/flags.make
r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o: /home/richstog/Documents/projects/r_engine/r_engine_core/src/r_engine_core/Application.cpp
r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o: r_engine_core/CMakeFiles/r_engine_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/richstog/Documents/projects/r_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o"
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o -MF CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o.d -o CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o -c /home/richstog/Documents/projects/r_engine/r_engine_core/src/r_engine_core/Application.cpp

r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.i"
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/richstog/Documents/projects/r_engine/r_engine_core/src/r_engine_core/Application.cpp > CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.i

r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.s"
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/richstog/Documents/projects/r_engine/r_engine_core/src/r_engine_core/Application.cpp -o CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.s

# Object files for target r_engine_core
r_engine_core_OBJECTS = \
"CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o"

# External object files for target r_engine_core
r_engine_core_EXTERNAL_OBJECTS =

r_engine_core/libr_engine_core.a: r_engine_core/CMakeFiles/r_engine_core.dir/src/r_engine_core/Application.cpp.o
r_engine_core/libr_engine_core.a: r_engine_core/CMakeFiles/r_engine_core.dir/build.make
r_engine_core/libr_engine_core.a: r_engine_core/CMakeFiles/r_engine_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/richstog/Documents/projects/r_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libr_engine_core.a"
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && $(CMAKE_COMMAND) -P CMakeFiles/r_engine_core.dir/cmake_clean_target.cmake
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r_engine_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
r_engine_core/CMakeFiles/r_engine_core.dir/build: r_engine_core/libr_engine_core.a
.PHONY : r_engine_core/CMakeFiles/r_engine_core.dir/build

r_engine_core/CMakeFiles/r_engine_core.dir/clean:
	cd /home/richstog/Documents/projects/r_engine/build/r_engine_core && $(CMAKE_COMMAND) -P CMakeFiles/r_engine_core.dir/cmake_clean.cmake
.PHONY : r_engine_core/CMakeFiles/r_engine_core.dir/clean

r_engine_core/CMakeFiles/r_engine_core.dir/depend:
	cd /home/richstog/Documents/projects/r_engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/richstog/Documents/projects/r_engine /home/richstog/Documents/projects/r_engine/r_engine_core /home/richstog/Documents/projects/r_engine/build /home/richstog/Documents/projects/r_engine/build/r_engine_core /home/richstog/Documents/projects/r_engine/build/r_engine_core/CMakeFiles/r_engine_core.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : r_engine_core/CMakeFiles/r_engine_core.dir/depend
