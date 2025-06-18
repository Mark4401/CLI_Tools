cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

project(CLI_Tools VERSION 0.0.1 LANGUAGES C CXX)

# Set C++ Standard to C++23 Preview
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C Standard to C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# For Windows builds: define UNICODE macros globally
if (WIN32)
    add_compile_definitions(UNICODE _UNICODE)
endif()
