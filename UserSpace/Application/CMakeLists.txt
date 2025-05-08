################################################################################
# @brief      CMake build configuration file.
#
#             This file defines how the current module is built using CMake.
#             It is part of the UserSpace application.
#
# @license    This project is publicly available on GitHub for viewing and
#             educational/reference purposes only. Redistribution, modification,
#             or commercial use of any portion of this code is strictly
#             prohibited without prior written permission from the author.
#
# @author     Kishwar Kumar
# @version    1.0
#
# @note       This code is not open source. Unauthorized use is not permitted.
################################################################################

cmake_minimum_required(VERSION 3.14)
project(EmbeddedApp)

# Use C++17 and other global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Show compiler/toolchain info (for debugging)
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "System Name : ${CMAKE_SYSTEM_NAME}")
message(STATUS "System Proc : ${CMAKE_SYSTEM_PROCESSOR}")

# Treat warnings as errors (can be turned off)
add_compile_options(-Wall -Werror)

# Add submodules
add_subdirectory(core)
add_subdirectory(services)
add_subdirectory(main)
