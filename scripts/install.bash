# ====================================================================================================================================
# @file       install.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 3rd February 2022 1:39:46 pm
# @modified   Sunday, 26th June 2022 11:43:55 am
# @project    mbed-utils
# @brief      Installs all dependencies of the project
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Install dependencies
$CPP_UTILS_HOME/scripts/install/dependencies.bash || exit 1
# Install external libraries
$CPP_UTILS_HOME/scripts/install/libraries/boost.bash || exit 1
