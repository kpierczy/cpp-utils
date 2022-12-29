#!/usr/bin/env bash
# ====================================================================================================================================
# @file       helpers.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 7th November 2021 3:08:11 pm
# @modified   Thursday, 29th December 2022 1:54:04 am
# @project    cpp-utils
# @brief      Implementation of helper functions
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ============================================================ Constants =========================================================== #

# List of toolchain's components
declare -a COMPONENTS=(
    prerequisites
    binutils
    gcc_base
    libc
    libc_aux
    gcc_final
    gcc_final_aux
    gdb
)

# List of build targets
declare -a TARGETS=(
    zlib
    gmp
    mpfr
    mpc
    isl
    elfutils
    expat
    cloog
    binutils
    gcc_base
    libc
    libc_aux
    gcc_final
    gcc_final_aux
    gdb
)

# List of build targets' names
declare -A TARGETS_NAMES=(
    [zlib]="Zlib library"
    [gmp]="GMP library"
    [mpfr]="MPFR library"
    [mpc]="MPC library"
    [isl]="ISL library"
    [elfutils]="Elfutils (libelf library)"
    [expat]="Expat library"
    [cloog]="Cloog library"
    [binutils]="binutils"
    [gcc_base]="GCC base"
    [libc]="libc library"
    [libc_aux]="libc library (auxiliary build)"
    [gcc_final]="GCC final"
    [gcc_final_aux]="GCC final (auxiliary build)"
    [gdb]="GDB debugger"
)

# List of flag sets
declare -a FLAG_SETS=(
    common
    ${TARGETS[@]}
)

# List of flag sets' names
declare -A FLAG_SETS_NAMES=(
    [common]="all components"
    [zlib]="Zlib library"
    [gmp]="GMP library"
    [mpfr]="MPFR library"
    [mpc]="MPC library"
    [isl]="ISL library"
    [elfutils]="Elfutils (libelf library)"
    [expat]="Expat library"
    [cloog]="Cloog library"
    [binutils]="binutils"
    [gcc_base]="GCC base"
    [libc]="libc library"
    [libc_aux]="libc library (auxiliary build)"
    [gcc_final]="GCC final"
    [gcc_final_aux]="GCC final (auxiliary build)"
    [gdb]="GDB debugger"
)

# ========================================================= General helpers ======================================================== #

# ---------------------------------------------------------------------------------------
# @brief Returns identifier of the current machine
# @outputs
#     identifier of the current machine 
# ---------------------------------------------------------------------------------------
function get_host() {

    # Get system name
    local uname_string=`uname | sed 'y/LINUXDARWIN/linuxdarwin/'`
    # Get machine
    local host_arch=`uname -m | sed 'y/XI/xi/'`

    # For Linux-based machines
    if [ "x$uname_string" == "xlinux" ] ; then
        echo "${host_arch}-linux-gnu"
    # For others
    else
        echo "<non-supported-host>"
    fi
}


# ---------------------------------------------------------------------------------------
# @brief Helper function checking whether @P string is name of the toolchain's 
#     flag set
# @param string
#     string to be inspected
# @returns
#     @retval @c 0 if @p string is a name of the toolchain's component
#     @retval @c 1 otherwise
# ---------------------------------------------------------------------------------------
function is_tolchain_flag_set() {

    # Arguments
    local string="$1"

    # Get list of components
    local -a valid_flag_sets=( "${FLAG_SETS[@]}" )
    # Convert to uppercase
    valid_flag_sets=( ${valid_flag_sets[@]^^} )
    
    # Check if a valid component given
    is_array_element 'valid_flag_sets' "${string^^}"
}


# ---------------------------------------------------------------------------------------
# @brief Performs a deep copy of the directory (resolves symbolic links)
# @param src
#     soruce directory
# @param dst
#     destination directory
# ---------------------------------------------------------------------------------------
function deep_copy_dir() {

    # Arguments
    local src="$1"
    local dst="$2"

    # Make destination dir
    mkdir -p "$dst"

    # Copy the directory by packing it and unpacking
    (cd "$src" && tar cf - .) | (cd "$dst" && tar xf -)
}

# ===================================================== Script-oriented helpers ==================================================== #

# ---------------------------------------------------------------------------------------
# @brief Helper alias designed to be used along with toolchain-building scripts basing
#    on the `gcc.bash` script. The aim of this alias is to automatically export 
#    environmental variables used by the script.
#
#    Alias searches all variables from the sorrounding scope and selects these
#    which match one of the patterns:
#
#         - TOOLCHAIN_*_CONFIG_FLAGS  [a]
#         - TOOLCHAIN_*_COMPILE_FLAGS [a]
#         - TOOLCHAIN_*_BUILD_ENV     [A]
#
#   [*] part expresses expected type of the variable (a - array, A - hash array).
#   These variables correspond to environmental variables accepted by `gcc.bash`. Next,
#   the routine matches (*) part with components and for each performs three actions:
#
#         1) Creates an copy of the (hash) array renamed to the
#            original name with removed 'TOOLCHAIN_' part
#         1) Serializies definition of the copied (hash) array into the 
#            TOOLCHAIN_EVAL_STRING string
#         2) Sets corresponding TOOLCHAIN_* environmental argument of
#            'gcc.bash' to the name of the copied array
#
#   By procesing these steps, user's script may ommit copy-pasting required to pass
#   all building flags to the underlying tool
#
# @note Taking into account described mechanism, the user's code should not `export`
#    mentioned variables. These should be declared as 'local' ones
# ---------------------------------------------------------------------------------------
alias gcc_parse_env='

    # Enable word splitting to parse flags in an apprpriate way
    localize_word_splitting
    push_stack "$IFS"
    enable_word_splitting

    # Parse envrionment
    declare -a  gcc_parse_env_config_flags=( $(declare -a | grep -oE -- " TOOLCHAIN_[[:alpha:]_]*_CONFIG_FLAGS")  ) || true
    declare -a gcc_parse_env_compile_flags=( $(declare -a | grep -oE -- " TOOLCHAIN_[[:alpha:]_]*_COMPILE_FLAGS") ) || true
    declare -a    gcc_parse_env_build_envs=( $(declare -A | grep -oE -- " TOOLCHAIN_[[:alpha:]_]*_BUILD_ENV")     ) || true

    # Initialize objects-injecting string
    export TOOLCHAIN_EVAL_STRING=""

    local gcc_parse_env_array_of_entities

    # Iterate over created arrays
    for gcc_parse_env_array_of_entities in "gcc_parse_env_config_flags" "gcc_parse_env_compile_flags" "gcc_parse_env_build_envs"; do

        # Get reference to the array
        local -n gcc_parse_env_array_of_entities_ref="$gcc_parse_env_array_of_entities"

        local gcc_parse_env_suffix

        # Select suffix
        case $gcc_parse_env_array_of_entities in
            "gcc_parse_env_config_flags"  ) gcc_parse_env_suffix="_CONFIG_FLAGS"  ;;
            "gcc_parse_env_compile_flags" ) gcc_parse_env_suffix="_COMPILE_FLAGS" ;;
            "gcc_parse_env_build_envs"    ) gcc_parse_env_suffix="_BUILD_ENV"     ;;
        esac

        local gcc_parse_env_entity

        # Parse config flags
        if ! is_array_empty "gcc_parse_env_array_of_entities_ref"; then
            for gcc_parse_env_entity in "${gcc_parse_env_array_of_entities_ref[@]}"; do

                # Get name of the component
                local gcc_parse_env_component_name="$gcc_parse_env_entity"
                gcc_parse_env_component_name="${gcc_parse_env_component_name#TOOLCHAIN_}"
                gcc_parse_env_component_name="${gcc_parse_env_component_name%$gcc_parse_env_suffix}"

                # If valid comonent name, parse it
                if is_tolchain_flag_set "$gcc_parse_env_component_name"; then

                    # Copy the array (in fact, make a reference to rename it)
                    eval "local -n ${gcc_parse_env_entity#TOOLCHAIN_}=${gcc_parse_env_entity}"
                    # Write down its definition to the toolchain builders environment
                    case $gcc_parse_env_array_of_entities in
                        "gcc_parse_env_build_envs" ) TOOLCHAIN_EVAL_STRING+=$(print_hash_array_def "${gcc_parse_env_entity#TOOLCHAIN_}") ;;
                        *                          ) TOOLCHAIN_EVAL_STRING+=$(print_array_def      "${gcc_parse_env_entity#TOOLCHAIN_}") ;;
                    esac
                    # Export name of the array
                    unset "$gcc_parse_env_entity"
                    eval "export $gcc_parse_env_entity=${gcc_parse_env_entity#TOOLCHAIN_}"
                    
                fi
            done
        fi
    done

    # Restor the prevous word-splitting separator
    pop_stack IFS
'
