# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
SHELL = /data/data/com.termux/files/usr/bin/sh

# The CMake executable.
CMAKE_COMMAND = /data/data/com.termux/files/usr/bin/cmake

# The command to remove a file.
RM = /data/data/com.termux/files/usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build

# Include any dependencies generated for this target.
include CMakeFiles/HxScript.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HxScript.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HxScript.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HxScript.dir/flags.make

CMakeFiles/HxScript.dir/codegen:
.PHONY : CMakeFiles/HxScript.dir/codegen

CMakeFiles/HxScript.dir/src/Main.c.o: CMakeFiles/HxScript.dir/flags.make
CMakeFiles/HxScript.dir/src/Main.c.o: /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/src/Main.c
CMakeFiles/HxScript.dir/src/Main.c.o: CMakeFiles/HxScript.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HxScript.dir/src/Main.c.o"
	/data/data/com.termux/files/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/HxScript.dir/src/Main.c.o -MF CMakeFiles/HxScript.dir/src/Main.c.o.d -o CMakeFiles/HxScript.dir/src/Main.c.o -c /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/src/Main.c

CMakeFiles/HxScript.dir/src/Main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/HxScript.dir/src/Main.c.i"
	/data/data/com.termux/files/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/src/Main.c > CMakeFiles/HxScript.dir/src/Main.c.i

CMakeFiles/HxScript.dir/src/Main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/HxScript.dir/src/Main.c.s"
	/data/data/com.termux/files/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/src/Main.c -o CMakeFiles/HxScript.dir/src/Main.c.s

# Object files for target HxScript
HxScript_OBJECTS = \
"CMakeFiles/HxScript.dir/src/Main.c.o"

# External object files for target HxScript
HxScript_EXTERNAL_OBJECTS =

HxScript: CMakeFiles/HxScript.dir/src/Main.c.o
HxScript: CMakeFiles/HxScript.dir/build.make
HxScript: CMakeFiles/HxScript.dir/compiler_depend.ts
HxScript: CMakeFiles/HxScript.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable HxScript"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HxScript.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HxScript.dir/build: HxScript
.PHONY : CMakeFiles/HxScript.dir/build

CMakeFiles/HxScript.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HxScript.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HxScript.dir/clean

CMakeFiles/HxScript.dir/depend:
	cd /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build /storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/build/CMakeFiles/HxScript.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HxScript.dir/depend

