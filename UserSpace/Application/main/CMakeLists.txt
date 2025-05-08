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

# Include all required headers
target_include_directories(EmbeddedApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/core/inc
    ${CMAKE_SOURCE_DIR}/core/interface
    ${CMAKE_SOURCE_DIR}/services/cli/inc
    ${CMAKE_SOURCE_DIR}/services/cli/interface
    ${CMAKE_SOURCE_DIR}/services/regression/inc
    ${CMAKE_SOURCE_DIR}/services/regression/interface
    ${CMAKE_SOURCE_DIR}/services/telnet/inc
    ${CMAKE_SOURCE_DIR}/services/telnet/interface
    ${CMAKE_SOURCE_DIR}/services/logging/inc
    ${CMAKE_SOURCE_DIR}/services/logging/interface
    ${CMAKE_SOURCE_DIR}/services/fileio/inc
    ${CMAKE_SOURCE_DIR}/services/fileio/interface
)

# Ensure these libraries are passed directly inside --whole-archive block
set(linkerset_static_libs "")
foreach(lib ${LINKERSET_LIBS})
    list(APPEND linkerset_static_libs "-Wl,--whole-archive" ${lib} "-Wl,--no-whole-archive")
endforeach()

target_link_libraries(EmbeddedApp PRIVATE ${linkerset_static_libs})

# Then link normally
target_link_libraries(EmbeddedApp PRIVATE core services)

# Compiler flags to match Makefile
target_compile_options(EmbeddedApp PRIVATE
    -Wall
    -Os
    -fdata-sections
    -ffunction-sections
    -std=c++17
    -fno-lto
    -fstack-protector-strong
    -O2
    -D_FORTIFY_SOURCE=2
    -Wformat
    -Wformat-security
    -Werror=format-security
    -mthumb
    -mfpu=neon-vfpv4
    -mfloat-abi=hard
    -mcpu=cortex-a7
    --sysroot=/opt/poky/4.0.21/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
)

# Linker flags
target_link_options(EmbeddedApp PRIVATE
    -static-libstdc++
    -static-libgcc
    -pthread
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/binaries/mapfile.map
    -Wl,-T${CMAKE_SOURCE_DIR}/linkerset.ld
    --sysroot=/opt/poky/4.0.21/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
)

# Output binary directory
set_target_properties(EmbeddedApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries
)

# strip binary
add_custom_command(TARGET EmbeddedApp POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} --strip-debug ${CMAKE_BINARY_DIR}/binaries/EmbeddedApp
    COMMENT "Stripping final binary in /binaries"
)
