# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/cmake-3.11.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.11.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luoqingming/coding/WZUtils/WZDataEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luoqingming/coding/WZUtils/WZDataEngine/build

# Include any dependencies generated for this target.
include test/CMakeFiles/li_gtest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/li_gtest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/li_gtest.dir/flags.make

test/CMakeFiles/li_gtest.dir/li_gtest.cpp.o: test/CMakeFiles/li_gtest.dir/flags.make
test/CMakeFiles/li_gtest.dir/li_gtest.cpp.o: ../test/li_gtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luoqingming/coding/WZUtils/WZDataEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/li_gtest.dir/li_gtest.cpp.o"
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/li_gtest.dir/li_gtest.cpp.o -c /home/luoqingming/coding/WZUtils/WZDataEngine/test/li_gtest.cpp

test/CMakeFiles/li_gtest.dir/li_gtest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/li_gtest.dir/li_gtest.cpp.i"
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luoqingming/coding/WZUtils/WZDataEngine/test/li_gtest.cpp > CMakeFiles/li_gtest.dir/li_gtest.cpp.i

test/CMakeFiles/li_gtest.dir/li_gtest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/li_gtest.dir/li_gtest.cpp.s"
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luoqingming/coding/WZUtils/WZDataEngine/test/li_gtest.cpp -o CMakeFiles/li_gtest.dir/li_gtest.cpp.s

# Object files for target li_gtest
li_gtest_OBJECTS = \
"CMakeFiles/li_gtest.dir/li_gtest.cpp.o"

# External object files for target li_gtest
li_gtest_EXTERNAL_OBJECTS =

../bin/li_gtest: test/CMakeFiles/li_gtest.dir/li_gtest.cpp.o
../bin/li_gtest: test/CMakeFiles/li_gtest.dir/build.make
../bin/li_gtest: ../lib/libmongodbengine.so.1.6
../bin/li_gtest: test/CMakeFiles/li_gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luoqingming/coding/WZUtils/WZDataEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/li_gtest"
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/li_gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/li_gtest.dir/build: ../bin/li_gtest

.PHONY : test/CMakeFiles/li_gtest.dir/build

test/CMakeFiles/li_gtest.dir/clean:
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build/test && $(CMAKE_COMMAND) -P CMakeFiles/li_gtest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/li_gtest.dir/clean

test/CMakeFiles/li_gtest.dir/depend:
	cd /home/luoqingming/coding/WZUtils/WZDataEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luoqingming/coding/WZUtils/WZDataEngine /home/luoqingming/coding/WZUtils/WZDataEngine/test /home/luoqingming/coding/WZUtils/WZDataEngine/build /home/luoqingming/coding/WZUtils/WZDataEngine/build/test /home/luoqingming/coding/WZUtils/WZDataEngine/build/test/CMakeFiles/li_gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/li_gtest.dir/depend

