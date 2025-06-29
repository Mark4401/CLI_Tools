# ======================================
# 🟨 Base Configuration
# ======================================
cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(CLI_Tools VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 🟨 Global build output directory
set(GLOBAL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Builds)

# ======================================
# 🟦 Build Toggles (Options)
# ======================================
option(BUILD_TOOL_A "Build Tool A" ON)
option(BUILD_TOOL_B "Build Tool B" ON)
option(BUILD_TOOL_C "Build Tool C" OFF) # Add more tools as needed

# ======================================
# 🟩 Macro: define_tool
# ======================================
function(define_tool TOOL_NAME SRC_LIST HDR_LIST INCLUDE_DIRS)
    add_executable(${TOOL_NAME} ${SRC_LIST} ${HDR_LIST})

    target_include_directories(${TOOL_NAME} PRIVATE ${INCLUDE_DIRS})

    if (WIN32)
        target_compile_definitions(${TOOL_NAME} PRIVATE UNICODE _UNICODE)
    endif()

    target_compile_options(${TOOL_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    set_target_properties(${TOOL_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/CLI_DB/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/CLI_DB/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/CLI_DB/$<CONFIG>
    )
endfunction()

# ======================================
# 🟥 Tool Definitions (Using Macro)
# ======================================

# Tool A
if (BUILD_TOOL_A)
    message(STATUS "🔨 Building Tool A")
    define_tool(
        ${PROJECT_NAME}
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/main.cpp;${CMAKE_CURRENT_SOURCE_DIR}/Src/CommandLineProcess.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Headers/CommandLineProcess.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Headers"
    )
endif()
# 
# # Tool B
# if (BUILD_TOOL_B)
#     message(STATUS "🔨 Building Tool B")
#     define_tool(
#         ToolB
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectB/Src/main.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectB/Headers/OtherHeader.h"
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectB/Headers"
#     )
# endif()
# 
# # Tool C (template for future tools)
# if (BUILD_TOOL_C)
#     message(STATUS "🔨 Building Tool C")
#     define_tool(
#         ToolC
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectC/Src/main.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectC/Headers/ToolC.h"
#         "${CMAKE_CURRENT_SOURCE_DIR}/ProjectC/Headers"
#     )
# endif()
