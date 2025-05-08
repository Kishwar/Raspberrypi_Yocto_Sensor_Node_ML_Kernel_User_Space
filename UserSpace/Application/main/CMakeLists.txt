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

file(GLOB_RECURSE MAIN_SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(EmbeddedApp ${MAIN_SRC})

target_include_directories(EmbeddedApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(EmbeddedApp core services)

# Compiler flags (Yocto-safe)
target_compile_options(EmbeddedApp PRIVATE
    -Wall
    -Os
    -fdata-sections
    -ffunction-sections
    -std=c++17
    -fno-lto
)

# Linker flags
target_link_options(EmbeddedApp PRIVATE
    -static-libstdc++
    -static-libgcc
    -pthread
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/binaries/mapfile.map
    -Wl,-T${CMAKE_SOURCE_DIR}/linkerset.ld
)

# strip binary
add_custom_command(TARGET EmbeddedApp POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} --strip-all ${CMAKE_BINARY_DIR}/binaries/EmbeddedApp
    COMMENT "Stripping final binary in /binaries"
)

# Set output binary directory
set_target_properties(EmbeddedApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries
)
