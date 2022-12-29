# ====================================================================================================================================
# @file       source_me.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 3rd February 2022 1:51:57 pm
# @modified   Thursday, 29th December 2022 1:05:55 am
# @project    cpp-utils
# @details
# 
#    This script should be sourced before starting work with the project. If the 'update' argument is passed to the script, 
#    the `git submodule update --init --recursive` will be run. This is optional action as updating boost repositories may 
#    take a longer while and it makes no sense to repeat this process at each source action. Moreover, the upstream 
#    repository may call the recursive git update itself in which case this action would be repeated slowing down the 
#    source process even more.
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Absolute path to the project's root directory
export CPP_UTILS_HOME="$(dirname "$(readlink -f "$BASH_SOURCE")")"

# Set this variable to true/false depending on whether you need a custom installation of boost headers
export CPP_UTILS_INSTALL_BOOST_HEADERS=false
# Set this variable to true/false depending on whether you need a custom installation of CMake
export CPP_UTILS_INSTALL_CMAKE=false

# ====================================================== Install dependencies ====================================================== #

# Update subprojects
if [[ "$1" == 'update' ]]; then
    if [[ $CPP_UTILS_INSTALL_BOOST_HEADERS == true ]]; then
        git submodule update --init --recursive
    else
        git submodule update --init --recursive extern/bash-utils
        git submodule update --init --recursive extern/frozen
    fi
fi

# Source bash-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash

# Install dependencies
$CPP_UTILS_HOME/scripts/install.bash || return 1
