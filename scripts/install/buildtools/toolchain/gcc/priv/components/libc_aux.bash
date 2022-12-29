#!/usr/bin/env bash
# ====================================================================================================================================
# @file       libc_aux.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 2:01:32 am
# @project    cpp-utils
# @brief      Installation routines for libc library (auxiliary build)
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source components-builders
source $FRAMEWORK_HOME/gcc/priv/components/libc/glibc.bash
source $FRAMEWORK_HOME/gcc/priv/components/libc/newlib.bash
source $FRAMEWORK_HOME/gcc/priv/components/libc/ulibc.bash

# =========================================================== Dispatcher =========================================================== #

function build_libc_aux() {

    # Dispatch build depending on the library version
    case ${opts[with_libc]} in
        'glibc'       ) build_glibc  'aux' || return 1 ;;
        'newlib'      ) build_newlib 'aux' || return 1 ;;
        'ulibc'       ) build_ulibc  'aux' || return 1 ;;
    esac

}
