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

#!/bin/bash

# Check for optional --verbose argument
if [[ "$1" == "--verbose" ]]; then
    VERBOSE_FLAG="--verbose"
    VERBOSE_CMAKE="-DCMAKE_VERBOSE_MAKEFILE=ON"
    echo "🔧 Building with verbose output..."
else
    VERBOSE_FLAG=""
    VERBOSE_CMAKE=""
    echo "🔧 Building (quiet mode)..."
fi

# 1. Clean or create build directory
rm -rf build
mkdir build
cd build || exit 1

# 2. Configure the build system
cmake .. ${VERBOSE_CMAKE}

# 3. Build
cmake --build . ${VERBOSE_FLAG}
