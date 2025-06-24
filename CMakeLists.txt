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

# Include path (for users of the library)
file(GLOB_RECURSE PROJECT_FILES
    
    Src/main.cpp

)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Headers>
)

# Step 4: Add the library's include directory
# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Math_Library/include
# )

# Step 5: Add the library's .lib folder
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Math_Library/lib)

# Step 6: Link the actual library file
# target_link_libraries(${PROJECT_NAME} PRIVATE Math_Library)

# Link flags
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8;-fexec-charset=UTF-8>")
add_compile_options("$<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8;-fexec-charset=UTF-8>")

# Set output directory (custom per build config)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Builds/$<CONFIG>
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Builds/$<CONFIG>
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Builds/$<CONFIG>
)