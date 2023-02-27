#!/usr/bin/env bash
# ====================================================================================================================================
# @file       install.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:28:20 pm
# @modified   Thursday, 29th December 2022 2:04:05 am
# @project    cpp-utils
# @brief      Script installing GCC toolchain's comonents
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Guarantee that the `bash-utils` project is sourced in the calling shell
if $([[ -z ${BASH_UTILS_HOME:+x} ]]); then
    echo -e \
            "[ERROR] BASH_UTILS_HOME variable is not defined or does not point to the root directory of bash-utils\n" \
            "       project. Please source source_me.bash file in the root directory of this project to provide\n"    \
            "       shell with required dependencies"
    exit 1
fi

# Source bash-utils library
source $BASH_UTILS_HOME/source_me.bash

# Localiza framework utilities
export FRAMEWORK_HOME="$(dirname "$(readlink -f "$BASH_SOURCE")")"

# Source default definitions library
source $FRAMEWORK_HOME/gcc/defaults.bash
# Source helper functions
source $FRAMEWORK_HOME/gcc/helpers.bash
# Source installation routine
source $FRAMEWORK_HOME/gcc/priv/install.bash

# ============================================================== Usage ============================================================= #

# Description of the script
declare cmd_description="Installs GCC toolchain components from source"

# Arguments' descriptions
declare -A pargs_description=(
    [components]="components to be installed"
)

# Components' description
get_heredoc components_description <<END
    Components:

            all building all components
       binutils building binutils
       gcc_base building GCC base of the GCC compillers ('all-gcc' target, built before libc)
           libc building libc
       libc_aux building libc (helper e.g. for building different version of libc)
      gcc_final building GCC compiller ('all' target, built after libc)
  gcc_final_aux building GCC compiller ('all' target, helper e.g. for building libstdcpp with different 
                         version of libc, built after libc)
            gdb building GDB debugger
END

# Options' descriptions
declare -A opts_description=(

    # General options
    [with_libc]="implementation of the standard library to be compiled"
    [build]="toolchain's build machine"
    [host]="toolchain's host machine"
    [target]="toolchain's target machine"
    [autocontinue]="if set, the script will not ask user before building each next stage of toolchain"
    [with_doc]="if set, the additional documentation will be genrated"
    [with_package]="if set, the <prefix> dir will be packaged into [tar.bz] placed under [PATH]"
    [verbose_tools]="f set, the building process will be run with verbose output of building tools"
    [force]=$(echo \
        "If set to non-empty valule, COMPONENTS will be rebuilt even if " \
        "it was marked as already built in TOOLCHAIN_BASEDIR directory"
    )
    
    # Directories
    [basename]="prefix of the toolchain's tools"
    [prefix]="insallation prefix of the toolchain"
    [basedir]=$(echo                                                             \
        "Base directory for toolchain's components. If provided, script "        \
        "will extract source files to this directory and keep them "             \
        "(in <basedir>/src/<component_name> directory) for future use "        \
        "to avoid repetition download. At the next run of the script, if "       \
        "the same directory is provided, no download (and possibly extraction) " \
        "of the source files would be required. "                                \
        "Moreover script marks builded packages by placing empty files "          \
        "(named '.compiled', '.installed', ...) in the build directories "       \
        "(under <basedir>/build/<component_name>) of the component. "     \
        "If component's build is requested again (e.g. in situation when "       \
        "the whole toolchain is build again after interrupted build), it "       \
        "will be skipped (as long as build version of the component matches) "   \
        "to avoid an overhead. "
    )

    # Versions
    [binutils_version]="version of binutils"
    [gcc_version]="version of GCC compiler"
    [gdb_version]="version of GDB debugger"
    [libc_version]=$(echo \
        "version of libc library (default: $TOOLCHAIN_GLIBC_VERSION [glibc] / " \
        "$TOOLCHAIN_NEWLIB_VERSION [newlib/newlib-nano] / $TOOLCHAIN_ULIBC_VERSION [ulibc] )"
    )
    # Utilities versions
    [zlib_version]="version of Zlib library"
    [gmp_version]="version of GMP library"
    [mpfr_version]="version of MPFR library"
    [mpc_version]="version of MPC library"
    [isl_version]="version of ISL library"
    [elfutils_version]="version of Elfutils (libelf library)"
    [expat_version]="version of Expat library"
    [cloog_version]="version of Cloog library"
    # Download URLs
    [binutils_url]="download URL of Binutils [not implemented - only default URL available]"
    [gcc_url]="download URL of GCC compiler [not implemented - only default URL available]"
    [gdb_url]="download URL of GDB debugger [not implemented - only default URL available]"
    [libc_url]=$(echo \
        "download URL of libc library (default: $TOOLCHAIN_GLIBC_URL_DEFAULT_SCHEME [glibc] / " \
        "$TOOLCHAIN_NEWLIB_URL_DEFAULT_SCHEME [newlib/newlib-nano] / $TOOLCHAIN_ULIBC_URL_DEFAULT_SCHEME [ulibc] )" \
        "[not implemented - only default URL available]"
    )
    # Download URLs (utilities)
    [zlib_url]="download URL of Zlib library [not implemented - only default URL available]"
    [gmp_url]="download URL of GMP library [not implemented - only default URL available]"
    [mpfr_url]="download URL of MPFR library [not implemented - only default URL available]"
    [mpc_url]="download URL of MPC library [not implemented - only default URL available]"
    [isl_url]="download URL of ISL library [not implemented - only default URL available]"
    [elfutils_url]="download URL of Elfutils (elflib library) [not implemented - only default URL available]"
    [expat_url]="download URL of Expat library [not implemented - only default URL available]"
    [cloog_url]="download URL of Cloog library [not implemented - only default URL available]"
    
)

# Envs' descriptions
declare -A envs_description=(
    [eval_string]=$(echo \
        "this variabla shall contain a string that should be evaluated by the build script before parsing build flags. " \
        "This mechanism provides a workaround to inject entities like array/hash arrays that are no passable by Linux " \
        "environment. It is desired specifically to pass hash arrays whose names are passed in the TOOLCHAIN_*_BUILD_ENV " \
        "and TOOLCHAIN_*_FLAGS variables to define custom environment for components' builds" \
    )
)

# Add envs' descriptions for all components
for set in ${FLAG_SETS[@]}; do
    envs_description[${set}_config_flags]="name of the hash array containing additional flags to be passed at configuration time of all ${FLAG_SETS_NAMES[$set]}"
    envs_description[${set}_compile_flags]="name of the hash array containing additional flags to be passed at compilation time of all ${FLAG_SETS_NAMES[$set]}"
    envs_description[${set}_build_env]="name of the hash array containing required environment to be set at build time of all ${FLAG_SETS_NAMES[$set]}"
done

# Additional info
get_heredoc source_description <<END
    Basedir folder:
            \033[31m.\033[0m
            ├── \033[34mdownloads\033[0m
            │   ├──────── <downloaded archieves>
            │   └──────── ...
            ├── \033[32msrc \033[0m
            │   ├── <extracted archieves>
            │   └── ...
            ├── \033[33mbuild \033[0m
            │   ├──── <per-target build directiories>
            │   └──── ...
            ├── \033[31minstall \033[0m
            │   ├────── host
            │   └────── target
            └── \u001b[34;1mpackage \033[0m

    $(set_bold)install/target$(reset_colors) will be set as a <prefix> when building *_aux components. On the other
    hand the $(set_bold)install/host$(reset_colors) directory will serve as <prefix> when building prerequisites.

    Source $(set_bold)$FRAMEWORK_HOME/gcc/helpers.bash$(reset_colors) to get additional functions and aliases that may
    help you implementing toolchain-building tools based on this script
END

# ====================================================== Default configuration ===================================================== #

# Logging context of the script
declare LOG_CONTEXT="gcc-toolchain"

# ====================================================== Positional arguments ====================================================== #

declare -A components_parg_def=( 
    [format]="COMPONENTS..."
    [name]="components"
    [type]="s"
    [default]='all'
    [variants]="all | binutils | gcc_base | gcc_final | gcc_final_aux | libc | libc_aux | gdb"
)

# ============================================================= Options ============================================================ #

declare -A        a_with_libc_opt_def=( [format]='--with-libc'        [type]='s' [name]='with_libc'        [default]="glibc" [varians]="glibc | newlib | ulibc" )
declare -A            b_build_opt_def=( [format]='--build'            [type]='s' [name]='build'            [default]="$(get_host)"                              )
declare -A             b_host_opt_def=( [format]='--host'             [type]='s' [name]='host'             [default]="$(get_host)"                              )
declare -A           b_target_opt_def=( [format]='--target'           [type]='s' [name]='target'           [default]="$(get_host)"                              )
declare -A     c_autocontinue_opt_def=( [format]='-y|--autocontinue'  [type]='f' [name]='autocontinue'                                                          )
declare -A         c_with_doc_opt_def=( [format]='--with-doc'         [type]='f' [name]='with_doc'                                                              )
declare -A     c_with_package_opt_def=( [format]='--with-package'     [type]='p' [name]='with_package'                                                          )
declare -A    c_verbose_tools_opt_def=( [format]='--verbose-tools'    [type]='f' [name]='verbose_tools'                                                         )
declare -A            c_force_opt_def=( [format]='--force'            [type]='f' [name]='force'                                                                 )
declare -A         d_basename_opt_def=( [format]='--basename'         [type]='s' [name]='basename'         [default]="gcc"                                      )
declare -A           e_prefix_opt_def=( [format]='--prefix'           [type]='s' [name]='prefix'           [default]="."                                        )
declare -A          e_basedir_opt_def=( [format]='--basedir'          [type]='s' [name]='basedir'          [default]="."                                        )
declare -A f_binutils_version_opt_def=( [format]='--binutils-version' [type]='s' [name]='binutils_version' [default]="$TOOLCHAIN_BINUTILS_DEFAULT_VERSION"      )
declare -A      f_gcc_version_opt_def=( [format]='--gcc-version'      [type]='s' [name]='gcc_version'      [default]="$TOOLCHAIN_GCC_DEFAULT_VERSION"           )
declare -A     f_libc_version_opt_def=( [format]='--libc-version'     [type]='s' [name]='libc_version'                                                          )
declare -A      f_gdb_version_opt_def=( [format]='--gdb-version'      [type]='s' [name]='gdb_version'      [default]="$TOOLCHAIN_GDB_DEFAULT_VERSION"           )
declare -A     g_zlib_version_opt_def=( [format]='--zlib-version'     [type]='s' [name]='zlib_version'     [default]="$TOOLCHAIN_ZLIB_DEFAULT_VERSION"          )
declare -A      g_gmp_version_opt_def=( [format]='--gmp-version'      [type]='s' [name]='gmp_version'      [default]="$TOOLCHAIN_GMP_DEFAULT_VERSION"           )
declare -A     g_mpfr_version_opt_def=( [format]='--mpfr-version'     [type]='s' [name]='mpfr_version'     [default]="$TOOLCHAIN_MPFR_DEFAULT_VERSION"          )
declare -A      g_mpc_version_opt_def=( [format]='--mpc-version'      [type]='s' [name]='mpc_version'      [default]="$TOOLCHAIN_MPC_DEFAULT_VERSION"           )
declare -A      g_isl_version_opt_def=( [format]='--isl-version'      [type]='s' [name]='isl_version'      [default]="$TOOLCHAIN_ISL_DEFAULT_VERSION"           )
declare -A g_elfutils_version_opt_def=( [format]='--elfutils-version' [type]='s' [name]='elfutils_version' [default]="$TOOLCHAIN_ELFUTILS_DEFAULT_VERSION"      )
declare -A    g_expat_version_opt_def=( [format]='--expat-version'    [type]='s' [name]='expat_version'    [default]="$TOOLCHAIN_EXPAT_DEFAULT_VERSION"         )
declare -A    g_cloog_version_opt_def=( [format]='--cloog-version'    [type]='s' [name]='cloog_version'    [default]="$TOOLCHAIN_CLOOG_DEFAULT_VERSION"         )
declare -A     h_binutils_url_opt_def=( [format]='--binutils-url'     [type]='s' [name]='binutils_url'     [default]="$TOOLCHAIN_BINUTILS_URL_DEFAULT_SCHEME"   )
declare -A          h_gcc_url_opt_def=( [format]='--gcc-url'          [type]='s' [name]='gcc_url'          [default]="$TOOLCHAIN_GCC_URL_DEFAULT_SCHEME"        )
declare -A         h_libc_url_opt_def=( [format]='--libc-url'         [type]='s' [name]='libc_url'                                                              )
declare -A          h_gdb_url_opt_def=( [format]='--gdb-url'          [type]='s' [name]='gdb_url'          [default]="$TOOLCHAIN_GDB_URL_DEFAULT_SCHEME"        )
declare -A         i_zlib_url_opt_def=( [format]='--zlib-url'         [type]='s' [name]='zlib_url'         [default]="$TOOLCHAIN_ZLIB_URL_DEFAULT_SCHEME"       )
declare -A          i_gmp_url_opt_def=( [format]='--gmp-url'          [type]='s' [name]='gmp_url'          [default]="$TOOLCHAIN_GMP_URL_DEFAULT_SCHEME"        )
declare -A         i_mpfr_url_opt_def=( [format]='--mpfr-url'         [type]='s' [name]='mpfr_url'         [default]="$TOOLCHAIN_MPFR_URL_DEFAULT_SCHEME"       )
declare -A          i_mpc_url_opt_def=( [format]='--mpc-url'          [type]='s' [name]='mpc_url'          [default]="$TOOLCHAIN_MPC_URL_DEFAULT_SCHEME"        )
declare -A          i_isl_url_opt_def=( [format]='--isl-url'          [type]='s' [name]='isl_url'          [default]="$TOOLCHAIN_ISL_URL_DEFAULT_SCHEME"        )
declare -A     i_elfutils_url_opt_def=( [format]='--elfutils-url'     [type]='s' [name]='elfutils_url'     [default]="$TOOLCHAIN_ELFUTILS_URL_DEFAULT_SCHEME"   )
declare -A        i_expat_url_opt_def=( [format]='--expat-url'        [type]='s' [name]='expat_url'        [default]="$TOOLCHAIN_EXPAT_URL_DEFAULT_SCHEME"      )
declare -A        i_cloog_url_opt_def=( [format]='--cloog-url'        [type]='s' [name]='cloog_url'        [default]="$TOOLCHAIN_CLOOG_URL_DEFAULT_SCHEME"      )

# =========================================================== Environment ========================================================== #

# Define standard envs' descriptors
declare -A eval_string_env_def=( [format]="TOOLCHAIN_EVAL_STRING" [name]="eval_string" [default]="" )

# Helper iterators
declare -a __alphabet=( {a..z} )
declare -i __i=0
# Add envs' descriptors for all components
for set in ${FLAG_SETS[@]}; do

    # Compute current letter
    declare __p=${__alphabet[$__i]}
    # Define descriptors
    eval declare -A  ${__p}_${set}_config_flags_env_def=\( [format]="TOOLCHAIN_${set^^}_CONFIG_FLAGS"  [name]="${set}_config_flags"  [default]="EMPTY_ENV" \)
    eval declare -A ${__p}_${set}_compile_flags_env_def=\( [format]="TOOLCHAIN_${set^^}_COMPILE_FLAGS" [name]="${set}_compile_flags" [default]="EMPTY_ENV" \)
    eval declare -A     ${__p}_${set}_build_env_env_def=\( [format]="TOOLCHAIN_${set^^}_BUILD_ENV"     [name]="${set}_build_env"     [default]="EMPTY_ENV" \)
    # Increment letter
    ((__i = $__i + 1))

done

# ============================================================== Main ============================================================== #

function main() {

    # Set help generator's configuration
    ARGUMENTS_DESCRIPTION_LENGTH_MAX=115
    # Parsing options
    declare -a PARSEARGS_OPTS
    PARSEARGS_OPTS+=( --with-help                                  )
    PARSEARGS_OPTS+=( --verbose                                    )
    PARSEARGS_OPTS+=( --with-append-description=source_description )

    # Parse arguments
    parse_arguments
    # If help requested, return
    if [[ $ret == '5' ]]; then
        return
    elif [[ $ret != '0' ]]; then
        return $ret
    fi

    # Log entry message
    log_info "$(set_bold)$(set_fblue)Running GCC toolchain builder...$(reset_colors)"
    log_info

    # Proceede installation
    install
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
