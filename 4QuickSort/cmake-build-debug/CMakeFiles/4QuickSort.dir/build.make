# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/4QuickSort.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/4QuickSort.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/4QuickSort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4QuickSort.dir/flags.make

CMakeFiles/4QuickSort.dir/QuickSort.cpp.o: CMakeFiles/4QuickSort.dir/flags.make
CMakeFiles/4QuickSort.dir/QuickSort.cpp.o: ../QuickSort.cpp
CMakeFiles/4QuickSort.dir/QuickSort.cpp.o: CMakeFiles/4QuickSort.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4QuickSort.dir/QuickSort.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/4QuickSort.dir/QuickSort.cpp.o -MF CMakeFiles/4QuickSort.dir/QuickSort.cpp.o.d -o CMakeFiles/4QuickSort.dir/QuickSort.cpp.o -c /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/QuickSort.cpp

CMakeFiles/4QuickSort.dir/QuickSort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4QuickSort.dir/QuickSort.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/QuickSort.cpp > CMakeFiles/4QuickSort.dir/QuickSort.cpp.i

CMakeFiles/4QuickSort.dir/QuickSort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4QuickSort.dir/QuickSort.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/QuickSort.cpp -o CMakeFiles/4QuickSort.dir/QuickSort.cpp.s

# Object files for target 4QuickSort
4QuickSort_OBJECTS = \
"CMakeFiles/4QuickSort.dir/QuickSort.cpp.o"

# External object files for target 4QuickSort
4QuickSort_EXTERNAL_OBJECTS =

4QuickSort: CMakeFiles/4QuickSort.dir/QuickSort.cpp.o
4QuickSort: CMakeFiles/4QuickSort.dir/build.make
4QuickSort: CMakeFiles/4QuickSort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 4QuickSort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/4QuickSort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4QuickSort.dir/build: 4QuickSort
.PHONY : CMakeFiles/4QuickSort.dir/build

CMakeFiles/4QuickSort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/4QuickSort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/4QuickSort.dir/clean

CMakeFiles/4QuickSort.dir/depend:
	cd /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug /mnt/e/202402-202406/C++Programs/23009200132/4QuickSort/cmake-build-debug/CMakeFiles/4QuickSort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/4QuickSort.dir/depend
