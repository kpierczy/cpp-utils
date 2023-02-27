#!/usr/bin/env bash
# ====================================================================================================================================
# @file       mpc.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 2:01:46 am
# @project    cpp-utils
# @brief      Installation routines for mpc library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source common function
source $FRAMEWORK_HOME/gcc/priv/components/common.bash

# ============================================================ Functions =========================================================== #

function build_mpc() {

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags
    CONFIG_FLAGS+=( "--build=${opts[build]}"                )
    CONFIG_FLAGS+=( "--host=${opts[host]}"                  )
    CONFIG_FLAGS+=( "--target=${opts[target]}"              )
    CONFIG_FLAGS+=( "--prefix=${dirs[install_host]}/usr"    )
    CONFIG_FLAGS+=( "--with-gmp=${dirs[install_host]}/usr"  )
    CONFIG_FLAGS+=( "--with-mpfr=${dirs[install_host]}/usr" )

    # -------------------------------------- Build --------------------------------------

    # Build the library
    build_component 'mpc'

}
