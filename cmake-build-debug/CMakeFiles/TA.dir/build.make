# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/ilya/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.10/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ilya/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.10/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ilya/CLionProjects/Theory-of-algorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TA.dir/flags.make

CMakeFiles/TA.dir/microchip.cpp.o: CMakeFiles/TA.dir/flags.make
CMakeFiles/TA.dir/microchip.cpp.o: ../microchip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TA.dir/microchip.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TA.dir/microchip.cpp.o -c /home/ilya/CLionProjects/Theory-of-algorithms/microchip.cpp

CMakeFiles/TA.dir/microchip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TA.dir/microchip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ilya/CLionProjects/Theory-of-algorithms/microchip.cpp > CMakeFiles/TA.dir/microchip.cpp.i

CMakeFiles/TA.dir/microchip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TA.dir/microchip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ilya/CLionProjects/Theory-of-algorithms/microchip.cpp -o CMakeFiles/TA.dir/microchip.cpp.s

CMakeFiles/TA.dir/archive.cpp.o: CMakeFiles/TA.dir/flags.make
CMakeFiles/TA.dir/archive.cpp.o: ../archive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TA.dir/archive.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TA.dir/archive.cpp.o -c /home/ilya/CLionProjects/Theory-of-algorithms/archive.cpp

CMakeFiles/TA.dir/archive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TA.dir/archive.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ilya/CLionProjects/Theory-of-algorithms/archive.cpp > CMakeFiles/TA.dir/archive.cpp.i

CMakeFiles/TA.dir/archive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TA.dir/archive.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ilya/CLionProjects/Theory-of-algorithms/archive.cpp -o CMakeFiles/TA.dir/archive.cpp.s

# Object files for target TA
TA_OBJECTS = \
"CMakeFiles/TA.dir/microchip.cpp.o" \
"CMakeFiles/TA.dir/archive.cpp.o"

# External object files for target TA
TA_EXTERNAL_OBJECTS =

TA: CMakeFiles/TA.dir/microchip.cpp.o
TA: CMakeFiles/TA.dir/archive.cpp.o
TA: CMakeFiles/TA.dir/build.make
TA: CMakeFiles/TA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable TA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TA.dir/build: TA

.PHONY : CMakeFiles/TA.dir/build

CMakeFiles/TA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TA.dir/clean

CMakeFiles/TA.dir/depend:
	cd /home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilya/CLionProjects/Theory-of-algorithms /home/ilya/CLionProjects/Theory-of-algorithms /home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug /home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug /home/ilya/CLionProjects/Theory-of-algorithms/cmake-build-debug/CMakeFiles/TA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TA.dir/depend

