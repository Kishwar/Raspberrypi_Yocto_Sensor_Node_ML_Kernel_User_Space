################################################################################
# @brief      Build Script to build firmware using CMake
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

# 1. Clean or create a build folder if needed
rm -rf build
mkdir build
cd build

# 2. Configure the build system
cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON

# 3. Now build with full verbosity
cmake --build . --verbose
