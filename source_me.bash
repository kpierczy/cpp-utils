# ====================================================================================================================================
# @file     source_me.bash
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Thursday, 3rd February 2022 1:51:57 pm
# @modified Monday, 14th February 2022 3:27:44 pm
# @project  mbed-utils
# @brief
#    
#    This script should be sourced before starting work with the project
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Absolute path to the project's root directory
export CPP_UTILS_HOME="$(dirname "$(readlink -f "$BASH_SOURCE")")"

# ====================================================== Install dependencies ====================================================== #

# Update subprojects
git submodule update --init --recursive

# Source bash-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash

# Install dependencies
$CPP_UTILS_HOME/scripts/install.bash
