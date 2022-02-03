# ====================================================================================================================================
# @file     install.bash
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Thursday, 3rd February 2022 1:39:46 pm
# @modified Thursday, 3rd February 2022 8:22:00 pm
# @project  mbed-utils
# @brief
#    
#    Installs all dependencies of the project
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Install dependencies
$CPP_UTILS_HOME/scripts/install/dependencies.bash
# Install external libraries
$CPP_UTILS_HOME/scripts/install/libraries/boost.bash
