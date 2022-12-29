#!/usr/bin/env bash
# ====================================================================================================================================
# @file       zlib.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 2:01:42 am
# @project    cpp-utils
# @brief      Installation routines for zlib library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source common function
source $FRAMEWORK_HOME/gcc/priv/components/common.bash

# ============================================================ Functions =========================================================== #

function build_zlib() {

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags (place in .../zlib foler to to prevent GCC linking this version of Zlib)
    CONFIG_FLAGS+=( "--prefix=${dirs[install_host]}/zlib" )

    # -------------------------------------- Build --------------------------------------

    # Build the library
    build_component 'zlib'

}
