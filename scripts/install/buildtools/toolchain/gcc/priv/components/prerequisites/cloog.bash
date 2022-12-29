#!/usr/bin/env bash
# ====================================================================================================================================
# @file       cloog.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 2:01:59 am
# @project    cpp-utils
# @brief      Installation routines for cloog library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source common function
source $FRAMEWORK_HOME/gcc/priv/components/common.bash

# ============================================================ Functions =========================================================== #

function build_cloog() {

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags
    CONFIG_FLAGS+=( "--build=${opts[build]}"               )
    CONFIG_FLAGS+=( "--host=${opts[host]}"                 )
    CONFIG_FLAGS+=( "--target=${opts[target]}"             )
    CONFIG_FLAGS+=( "--prefix=${dirs[install_host]}/usr"   )
    CONFIG_FLAGS+=( "--with-gmp=${dirs[install_host]}/usr" )
    CONFIG_FLAGS+=( "--with-isl=${dirs[install_host]}/usr" )

    # -------------------------------------- Build --------------------------------------

    # Build the library
    build_component 'cloog'
}
