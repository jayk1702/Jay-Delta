# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /home/dtiot-2024/Qt/Tools/CMake/bin/cmake

# The command to remove a file.
RM = /home/dtiot-2024/Qt/Tools/CMake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dtiot-2024/signUp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug

# Include any dependencies generated for this target.
include CMakeFiles/signUp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/signUp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/signUp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/signUp.dir/flags.make

signUp_autogen/timestamp: /home/dtiot-2024/Qt/6.8.3/gcc_64/libexec/moc
signUp_autogen/timestamp: /home/dtiot-2024/Qt/6.8.3/gcc_64/libexec/uic
signUp_autogen/timestamp: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target signUp"
	/home/dtiot-2024/Qt/Tools/CMake/bin/cmake -E cmake_autogen /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles/signUp_autogen.dir/AutogenInfo.json Debug
	/home/dtiot-2024/Qt/Tools/CMake/bin/cmake -E touch /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/signUp_autogen/timestamp

CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o: CMakeFiles/signUp.dir/flags.make
CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o: signUp_autogen/mocs_compilation.cpp
CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o -MF CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o -c /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/signUp_autogen/mocs_compilation.cpp

CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/signUp_autogen/mocs_compilation.cpp > CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.i

CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/signUp_autogen/mocs_compilation.cpp -o CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.s

CMakeFiles/signUp.dir/main.cpp.o: CMakeFiles/signUp.dir/flags.make
CMakeFiles/signUp.dir/main.cpp.o: /home/dtiot-2024/signUp/main.cpp
CMakeFiles/signUp.dir/main.cpp.o: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/signUp.dir/main.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/signUp.dir/main.cpp.o -MF CMakeFiles/signUp.dir/main.cpp.o.d -o CMakeFiles/signUp.dir/main.cpp.o -c /home/dtiot-2024/signUp/main.cpp

CMakeFiles/signUp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/signUp.dir/main.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtiot-2024/signUp/main.cpp > CMakeFiles/signUp.dir/main.cpp.i

CMakeFiles/signUp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/signUp.dir/main.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtiot-2024/signUp/main.cpp -o CMakeFiles/signUp.dir/main.cpp.s

CMakeFiles/signUp.dir/mainwindow.cpp.o: CMakeFiles/signUp.dir/flags.make
CMakeFiles/signUp.dir/mainwindow.cpp.o: /home/dtiot-2024/signUp/mainwindow.cpp
CMakeFiles/signUp.dir/mainwindow.cpp.o: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/signUp.dir/mainwindow.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/signUp.dir/mainwindow.cpp.o -MF CMakeFiles/signUp.dir/mainwindow.cpp.o.d -o CMakeFiles/signUp.dir/mainwindow.cpp.o -c /home/dtiot-2024/signUp/mainwindow.cpp

CMakeFiles/signUp.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/signUp.dir/mainwindow.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtiot-2024/signUp/mainwindow.cpp > CMakeFiles/signUp.dir/mainwindow.cpp.i

CMakeFiles/signUp.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/signUp.dir/mainwindow.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtiot-2024/signUp/mainwindow.cpp -o CMakeFiles/signUp.dir/mainwindow.cpp.s

CMakeFiles/signUp.dir/signuppage.cpp.o: CMakeFiles/signUp.dir/flags.make
CMakeFiles/signUp.dir/signuppage.cpp.o: /home/dtiot-2024/signUp/signuppage.cpp
CMakeFiles/signUp.dir/signuppage.cpp.o: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/signUp.dir/signuppage.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/signUp.dir/signuppage.cpp.o -MF CMakeFiles/signUp.dir/signuppage.cpp.o.d -o CMakeFiles/signUp.dir/signuppage.cpp.o -c /home/dtiot-2024/signUp/signuppage.cpp

CMakeFiles/signUp.dir/signuppage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/signUp.dir/signuppage.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtiot-2024/signUp/signuppage.cpp > CMakeFiles/signUp.dir/signuppage.cpp.i

CMakeFiles/signUp.dir/signuppage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/signUp.dir/signuppage.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtiot-2024/signUp/signuppage.cpp -o CMakeFiles/signUp.dir/signuppage.cpp.s

CMakeFiles/signUp.dir/database.cpp.o: CMakeFiles/signUp.dir/flags.make
CMakeFiles/signUp.dir/database.cpp.o: /home/dtiot-2024/signUp/database.cpp
CMakeFiles/signUp.dir/database.cpp.o: CMakeFiles/signUp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/signUp.dir/database.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/signUp.dir/database.cpp.o -MF CMakeFiles/signUp.dir/database.cpp.o.d -o CMakeFiles/signUp.dir/database.cpp.o -c /home/dtiot-2024/signUp/database.cpp

CMakeFiles/signUp.dir/database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/signUp.dir/database.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtiot-2024/signUp/database.cpp > CMakeFiles/signUp.dir/database.cpp.i

CMakeFiles/signUp.dir/database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/signUp.dir/database.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtiot-2024/signUp/database.cpp -o CMakeFiles/signUp.dir/database.cpp.s

# Object files for target signUp
signUp_OBJECTS = \
"CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/signUp.dir/main.cpp.o" \
"CMakeFiles/signUp.dir/mainwindow.cpp.o" \
"CMakeFiles/signUp.dir/signuppage.cpp.o" \
"CMakeFiles/signUp.dir/database.cpp.o"

# External object files for target signUp
signUp_EXTERNAL_OBJECTS =

signUp: CMakeFiles/signUp.dir/signUp_autogen/mocs_compilation.cpp.o
signUp: CMakeFiles/signUp.dir/main.cpp.o
signUp: CMakeFiles/signUp.dir/mainwindow.cpp.o
signUp: CMakeFiles/signUp.dir/signuppage.cpp.o
signUp: CMakeFiles/signUp.dir/database.cpp.o
signUp: CMakeFiles/signUp.dir/build.make
signUp: /home/dtiot-2024/Qt/6.8.3/gcc_64/lib/libQt6Widgets.so.6.8.3
signUp: /home/dtiot-2024/Qt/6.8.3/gcc_64/lib/libQt6Sql.so.6.8.3
signUp: /home/dtiot-2024/Qt/6.8.3/gcc_64/lib/libQt6Gui.so.6.8.3
signUp: /usr/lib/x86_64-linux-gnu/libGL.so
signUp: /home/dtiot-2024/Qt/6.8.3/gcc_64/lib/libQt6Core.so.6.8.3
signUp: CMakeFiles/signUp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable signUp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/signUp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/signUp.dir/build: signUp
.PHONY : CMakeFiles/signUp.dir/build

CMakeFiles/signUp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/signUp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/signUp.dir/clean

CMakeFiles/signUp.dir/depend: signUp_autogen/timestamp
	cd /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dtiot-2024/signUp /home/dtiot-2024/signUp /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug /home/dtiot-2024/signUp/build/Desktop_Qt_6_8_3-Debug/CMakeFiles/signUp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/signUp.dir/depend

