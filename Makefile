# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/sjoon/Documents/git/VectorSimGen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sjoon/Documents/git/VectorSimGen

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sjoon/Documents/git/VectorSimGen/CMakeFiles /home/sjoon/Documents/git/VectorSimGen//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sjoon/Documents/git/VectorSimGen/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /home/sjoon/Documents/git/VectorSimGen/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named vsg

# Build rule for target.
vsg: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 vsg
.PHONY : vsg

# fast build rule for target.
vsg/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/build
.PHONY : vsg/fast

#=============================================================================
# Target rules for targets named vsg-testbin

# Build rule for target.
vsg-testbin: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 vsg-testbin
.PHONY : vsg-testbin

# fast build rule for target.
vsg-testbin/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/build
.PHONY : vsg-testbin/fast

#=============================================================================
# Target rules for targets named spdlog

# Build rule for target.
spdlog: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 spdlog
.PHONY : spdlog

# fast build rule for target.
spdlog/fast:
	$(MAKE) $(MAKESILENT) -f extern/spdlog/CMakeFiles/spdlog.dir/build.make extern/spdlog/CMakeFiles/spdlog.dir/build
.PHONY : spdlog/fast

src/VectorReader.o: src/VectorReader.cc.o
.PHONY : src/VectorReader.o

# target to build an object file
src/VectorReader.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/VectorReader.cc.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/VectorReader.cc.o
.PHONY : src/VectorReader.cc.o

src/VectorReader.i: src/VectorReader.cc.i
.PHONY : src/VectorReader.i

# target to preprocess a source file
src/VectorReader.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/VectorReader.cc.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/VectorReader.cc.i
.PHONY : src/VectorReader.cc.i

src/VectorReader.s: src/VectorReader.cc.s
.PHONY : src/VectorReader.s

# target to generate assembly for a file
src/VectorReader.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/VectorReader.cc.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/VectorReader.cc.s
.PHONY : src/VectorReader.cc.s

src/test/main.o: src/test/main.cc.o
.PHONY : src/test/main.o

# target to build an object file
src/test/main.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/test/main.cc.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/test/main.cc.o
.PHONY : src/test/main.cc.o

src/test/main.i: src/test/main.cc.i
.PHONY : src/test/main.i

# target to preprocess a source file
src/test/main.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/test/main.cc.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/test/main.cc.i
.PHONY : src/test/main.cc.i

src/test/main.s: src/test/main.cc.s
.PHONY : src/test/main.s

# target to generate assembly for a file
src/test/main.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg.dir/build.make CMakeFiles/vsg.dir/src/test/main.cc.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/vsg-testbin.dir/build.make CMakeFiles/vsg-testbin.dir/src/test/main.cc.s
.PHONY : src/test/main.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... spdlog"
	@echo "... vsg"
	@echo "... vsg-testbin"
	@echo "... src/VectorReader.o"
	@echo "... src/VectorReader.i"
	@echo "... src/VectorReader.s"
	@echo "... src/test/main.o"
	@echo "... src/test/main.i"
	@echo "... src/test/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /home/sjoon/Documents/git/VectorSimGen/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
