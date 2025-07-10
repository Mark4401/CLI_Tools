# ======================================
# 🟨 Base Configuration
# ======================================
cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(CLI_Tools VERSION 0.0.5 LANGUAGES C CXX)

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
option(BUILD_TOOL_C "Build Tool C" ON) # Add more tools as needed

# ======================================
# 🟩 Macro: define_tool
# ======================================
# define_tool(name sources headers include_dir sub-folder)
function(define_tool TOOL_NAME SRC_LIST HDR_LIST INCLUDE_DIRS SUBFOLDER)
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
        ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
    )
endfunction()

# ======================================
# 🟥 Tool Definitions (Using Macro)
# ======================================


# Tool A
if (BUILD_TOOL_A)
    message(STATUS "🔨 Building Tool A")

    set(ACTIVE_CLI_TOOL_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Active_CLI_tool/Src/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Active_CLI_tool/Src/CommandLineProcess.cpp"
    )

    set(ACTIVE_CLI_TOOL_HDRS
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Active_CLI_tool/Headers/CommandLineProcess.h"
    )

    define_tool(
        Active_CLI_tool
        "${ACTIVE_CLI_TOOL_SRCS}"
        "${ACTIVE_CLI_TOOL_HDRS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Active_CLI_tool/Headers"
        "Active_CLI_tool"  # 👈 This becomes your sub-folder under Debug/Release
    )
endif()

# tool B

if(BUILD_TOOL_B)
    message(STATUS "Demo Argument Pars Building in Progress....")

    set(Demo_CLI_FIS_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Demo_CLI_FIS/Src/Source.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Demo_CLI_FIS/Src/CMD_literals.cpp"        
    )
    set(Demo_CLI_FIS_HDRS
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Demo_CLI_FIS/Headers/CMD_literals.h"
    )

    define_tool(
        Demo_CLI
        "${Demo_CLI_FIS_SRCS}"
        "${Demo_CLI_FIS_HDRS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Archive/Demo_CLI_FIS/Headers"
        "Demo_CLI"
    )

endif()


if(BUILD_TOOL_C)

    message(STATUS "Building in Progress....")

    set(SRC_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Src/Source.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Src/CommandLineProcess.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Src/PlayerCampainGame.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Src/DialogLookUp.cpp"
    )
    set(HDR_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Include/internal.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Include/CommandLineProcess.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Include/PlayerCampainGame.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Include/DialogLookUp.h"
    )

    define_tool(
        CommandLine_tool
        "${SRC_DIR}"
        "${HDR_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Primary_Project/Include"
        "CommandLine_tool"
    )
endif()

