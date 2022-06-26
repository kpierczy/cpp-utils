# ====================================================================================================================================
# @file       install_cmake.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 21st November 2021 5:18:41 pm
# @modified   Sunday, 26th June 2022 1:14:45 pm
# @project    mbed-utils
# @brief      Installation script for CMake
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source bsah-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash

# ========================================================== Configuration ========================================================= #

# CMake version (host: https://github.com/Kitware/CMake/releases)
declare VERSION=3.22.0

# ============================================================ Functions =========================================================== #

main() {

    # If CMake installation is not needed, exit
    if [[$CPP_UTILS_INSTALL_CMAKE != true ]]; then
        exit 0
    fi

    # If CMake is NOT already installed
    if [[ ! -e $CPP_UTILS_HOME/tools/cmake ]]; then

        # Install toolchain using bash-utils
        $BASH_UTILS_HOME/bin/install/buildtools/cmake.bash bin $VERSION \
            --prefix="$CPP_UTILS_HOME/tools/cmake"                     \
            --cleanup                                                   \
        || exit 1

    fi

}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
