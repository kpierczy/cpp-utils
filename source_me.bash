# ====================================================================================================================================
# @file       source_me.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 3rd February 2022 1:51:57 pm
# @modified   Monday, 27th February 2023 10:02:29 pm
# @project    cpp-utils
# @details    This script should be sourced before starting work with the project. If the 'update' argument is passed to the script,
#             the `git submodule update --init --recursive` will be run. This is optional action as updating boost repositories may
#             take a longer while and it makes no sense to repeat this process at each source action. Moreover, the upstream
#             repository may call the recursive git update itself in which case this action would be repeated slowing down the
#             source process even more.
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
$CPP_UTILS_HOME/tools/install/dependencies.bash || return 1
