# CMake for my little project.

cmake_minimum_required(VERSION 3.10)        # REQUIRED Must come first
project(flaggr LANGUAGES C)                 # REQUIRED Must come second
# flaggr becomes ${PROJECT_NAME}

set(CMAKE_C_STANDARD 11)                    # Set standard
set(CMAKE_C_FLAGS "-Wall -Wextra -g")       # Compiler flags

# Set the output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(flags_lib src/libs/flags.c)
target_include_directories(flags_lib PUBLIC include) # Makes header visible to executables

# GLOB_RECURSE = Go through subfodler aswell
# SRC_FILES = Variable created
# CONFIGURE_DEPENDS = Re runs CMake if new files are added
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.c") 

# Create the executable file
add_executable(${PROJECT_NAME} ${SRC})

# Link compiled libraries 
# m = math.h lib
# pthread = pthread.h lib
target_link_libraries(${PROJECT_NAME} PRIVATE flags_lib m pthread)

