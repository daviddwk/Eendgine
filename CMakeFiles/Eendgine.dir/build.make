# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/david/Code/TestEend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Code/TestEend/build

# Include any dependencies generated for this target.
include lib/Eendgine/CMakeFiles/Eendgine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/Eendgine/CMakeFiles/Eendgine.dir/progress.make

# Include the compile flags for this target's objects.
include lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make

lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o: /home/david/Code/TestEend/lib/Eendgine/camera.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o -MF CMakeFiles/Eendgine.dir/camera.cpp.o.d -o CMakeFiles/Eendgine.dir/camera.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/camera.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/camera.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/camera.cpp > CMakeFiles/Eendgine.dir/camera.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/camera.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/camera.cpp -o CMakeFiles/Eendgine.dir/camera.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o: /home/david/Code/TestEend/lib/Eendgine/collisionGeometry.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o -MF CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o.d -o CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/collisionGeometry.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/collisionGeometry.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/collisionGeometry.cpp > CMakeFiles/Eendgine.dir/collisionGeometry.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/collisionGeometry.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/collisionGeometry.cpp -o CMakeFiles/Eendgine.dir/collisionGeometry.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o: /home/david/Code/TestEend/lib/Eendgine/entityBatches.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o -MF CMakeFiles/Eendgine.dir/entityBatches.cpp.o.d -o CMakeFiles/Eendgine.dir/entityBatches.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/entityBatches.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/entityBatches.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/entityBatches.cpp > CMakeFiles/Eendgine.dir/entityBatches.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/entityBatches.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/entityBatches.cpp -o CMakeFiles/Eendgine.dir/entityBatches.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o: /home/david/Code/TestEend/lib/Eendgine/fatalError.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o -MF CMakeFiles/Eendgine.dir/fatalError.cpp.o.d -o CMakeFiles/Eendgine.dir/fatalError.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/fatalError.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/fatalError.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/fatalError.cpp > CMakeFiles/Eendgine.dir/fatalError.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/fatalError.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/fatalError.cpp -o CMakeFiles/Eendgine.dir/fatalError.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o: /home/david/Code/TestEend/lib/Eendgine/frameLimiter.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o -MF CMakeFiles/Eendgine.dir/frameLimiter.cpp.o.d -o CMakeFiles/Eendgine.dir/frameLimiter.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/frameLimiter.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/frameLimiter.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/frameLimiter.cpp > CMakeFiles/Eendgine.dir/frameLimiter.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/frameLimiter.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/frameLimiter.cpp -o CMakeFiles/Eendgine.dir/frameLimiter.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o: /home/david/Code/TestEend/lib/Eendgine/info.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o -MF CMakeFiles/Eendgine.dir/info.cpp.o.d -o CMakeFiles/Eendgine.dir/info.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/info.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/info.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/info.cpp > CMakeFiles/Eendgine.dir/info.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/info.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/info.cpp -o CMakeFiles/Eendgine.dir/info.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o: /home/david/Code/TestEend/lib/Eendgine/inputManager.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o -MF CMakeFiles/Eendgine.dir/inputManager.cpp.o.d -o CMakeFiles/Eendgine.dir/inputManager.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/inputManager.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/inputManager.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/inputManager.cpp > CMakeFiles/Eendgine.dir/inputManager.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/inputManager.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/inputManager.cpp -o CMakeFiles/Eendgine.dir/inputManager.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o: /home/david/Code/TestEend/lib/Eendgine/loadModel.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o -MF CMakeFiles/Eendgine.dir/loadModel.cpp.o.d -o CMakeFiles/Eendgine.dir/loadModel.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/loadModel.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/loadModel.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/loadModel.cpp > CMakeFiles/Eendgine.dir/loadModel.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/loadModel.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/loadModel.cpp -o CMakeFiles/Eendgine.dir/loadModel.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o: /home/david/Code/TestEend/lib/Eendgine/model.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o -MF CMakeFiles/Eendgine.dir/model.cpp.o.d -o CMakeFiles/Eendgine.dir/model.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/model.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/model.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/model.cpp > CMakeFiles/Eendgine.dir/model.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/model.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/model.cpp -o CMakeFiles/Eendgine.dir/model.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o: /home/david/Code/TestEend/lib/Eendgine/random.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o -MF CMakeFiles/Eendgine.dir/random.cpp.o.d -o CMakeFiles/Eendgine.dir/random.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/random.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/random.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/random.cpp > CMakeFiles/Eendgine.dir/random.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/random.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/random.cpp -o CMakeFiles/Eendgine.dir/random.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o: /home/david/Code/TestEend/lib/Eendgine/screen.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o -MF CMakeFiles/Eendgine.dir/screen.cpp.o.d -o CMakeFiles/Eendgine.dir/screen.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/screen.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/screen.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/screen.cpp > CMakeFiles/Eendgine.dir/screen.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/screen.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/screen.cpp -o CMakeFiles/Eendgine.dir/screen.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o: /home/david/Code/TestEend/lib/Eendgine/shader.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o -MF CMakeFiles/Eendgine.dir/shader.cpp.o.d -o CMakeFiles/Eendgine.dir/shader.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/shader.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/shader.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/shader.cpp > CMakeFiles/Eendgine.dir/shader.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/shader.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/shader.cpp -o CMakeFiles/Eendgine.dir/shader.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o: /home/david/Code/TestEend/lib/Eendgine/shaders.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o -MF CMakeFiles/Eendgine.dir/shaders.cpp.o.d -o CMakeFiles/Eendgine.dir/shaders.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/shaders.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/shaders.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/shaders.cpp > CMakeFiles/Eendgine.dir/shaders.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/shaders.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/shaders.cpp -o CMakeFiles/Eendgine.dir/shaders.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o: /home/david/Code/TestEend/lib/Eendgine/sprite.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o -MF CMakeFiles/Eendgine.dir/sprite.cpp.o.d -o CMakeFiles/Eendgine.dir/sprite.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/sprite.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/sprite.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/sprite.cpp > CMakeFiles/Eendgine.dir/sprite.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/sprite.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/sprite.cpp -o CMakeFiles/Eendgine.dir/sprite.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o: /home/david/Code/TestEend/lib/Eendgine/texture.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o -MF CMakeFiles/Eendgine.dir/texture.cpp.o.d -o CMakeFiles/Eendgine.dir/texture.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/texture.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/texture.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/texture.cpp > CMakeFiles/Eendgine.dir/texture.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/texture.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/texture.cpp -o CMakeFiles/Eendgine.dir/texture.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o: /home/david/Code/TestEend/lib/Eendgine/textureCache.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o -MF CMakeFiles/Eendgine.dir/textureCache.cpp.o.d -o CMakeFiles/Eendgine.dir/textureCache.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/textureCache.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/textureCache.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/textureCache.cpp > CMakeFiles/Eendgine.dir/textureCache.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/textureCache.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/textureCache.cpp -o CMakeFiles/Eendgine.dir/textureCache.cpp.s

lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/flags.make
lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o: /home/david/Code/TestEend/lib/Eendgine/window.cpp
lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o: lib/Eendgine/CMakeFiles/Eendgine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o -MF CMakeFiles/Eendgine.dir/window.cpp.o.d -o CMakeFiles/Eendgine.dir/window.cpp.o -c /home/david/Code/TestEend/lib/Eendgine/window.cpp

lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Eendgine.dir/window.cpp.i"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Code/TestEend/lib/Eendgine/window.cpp > CMakeFiles/Eendgine.dir/window.cpp.i

lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Eendgine.dir/window.cpp.s"
	cd /home/david/Code/TestEend/build/lib/Eendgine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Code/TestEend/lib/Eendgine/window.cpp -o CMakeFiles/Eendgine.dir/window.cpp.s

# Object files for target Eendgine
Eendgine_OBJECTS = \
"CMakeFiles/Eendgine.dir/camera.cpp.o" \
"CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o" \
"CMakeFiles/Eendgine.dir/entityBatches.cpp.o" \
"CMakeFiles/Eendgine.dir/fatalError.cpp.o" \
"CMakeFiles/Eendgine.dir/frameLimiter.cpp.o" \
"CMakeFiles/Eendgine.dir/info.cpp.o" \
"CMakeFiles/Eendgine.dir/inputManager.cpp.o" \
"CMakeFiles/Eendgine.dir/loadModel.cpp.o" \
"CMakeFiles/Eendgine.dir/model.cpp.o" \
"CMakeFiles/Eendgine.dir/random.cpp.o" \
"CMakeFiles/Eendgine.dir/screen.cpp.o" \
"CMakeFiles/Eendgine.dir/shader.cpp.o" \
"CMakeFiles/Eendgine.dir/shaders.cpp.o" \
"CMakeFiles/Eendgine.dir/sprite.cpp.o" \
"CMakeFiles/Eendgine.dir/texture.cpp.o" \
"CMakeFiles/Eendgine.dir/textureCache.cpp.o" \
"CMakeFiles/Eendgine.dir/window.cpp.o"

# External object files for target Eendgine
Eendgine_EXTERNAL_OBJECTS =

lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/camera.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/collisionGeometry.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/entityBatches.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/fatalError.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/frameLimiter.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/info.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/inputManager.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/loadModel.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/model.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/random.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/screen.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/shader.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/shaders.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/sprite.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/texture.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/textureCache.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/window.cpp.o
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/build.make
lib/Eendgine/libEendgine.a: lib/Eendgine/CMakeFiles/Eendgine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/david/Code/TestEend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX static library libEendgine.a"
	cd /home/david/Code/TestEend/build/lib/Eendgine && $(CMAKE_COMMAND) -P CMakeFiles/Eendgine.dir/cmake_clean_target.cmake
	cd /home/david/Code/TestEend/build/lib/Eendgine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Eendgine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/Eendgine/CMakeFiles/Eendgine.dir/build: lib/Eendgine/libEendgine.a
.PHONY : lib/Eendgine/CMakeFiles/Eendgine.dir/build

lib/Eendgine/CMakeFiles/Eendgine.dir/clean:
	cd /home/david/Code/TestEend/build/lib/Eendgine && $(CMAKE_COMMAND) -P CMakeFiles/Eendgine.dir/cmake_clean.cmake
.PHONY : lib/Eendgine/CMakeFiles/Eendgine.dir/clean

lib/Eendgine/CMakeFiles/Eendgine.dir/depend:
	cd /home/david/Code/TestEend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Code/TestEend /home/david/Code/TestEend/lib/Eendgine /home/david/Code/TestEend/build /home/david/Code/TestEend/build/lib/Eendgine /home/david/Code/TestEend/build/lib/Eendgine/CMakeFiles/Eendgine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/Eendgine/CMakeFiles/Eendgine.dir/depend

