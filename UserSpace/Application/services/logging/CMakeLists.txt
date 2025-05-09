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

file(GLOB_RECURSE LOGGING_SRC CONFIGURE_DEPENDS src/*.cpp)
add_library(services_logging ${LOGGING_SRC})

target_include_directories(services_logging PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

target_link_libraries(services_logging
                      core
                      services_telnet)
