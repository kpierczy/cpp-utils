#!/usr/bin/env bash
# ====================================================================================================================================
# @file       arm-embedded-toolchain.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 21st November 2021 1:51:48 pm
# @modified   Thursday, 29th December 2022 1:53:46 am
# @project    cpp-utils
# @brief      Installs the given version of the ARM-Embedded-Toolchain
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

# ============================================================== Usage ============================================================= #

# Description of the script
declare cmd_description=$(echo \
    "Installs requested version of the ARM-Embedded-Toolchain binaries for the " \
    "current platform (x86_64 or aarch64 supported)"
)

# Arguments' descriptions
declare -A pargs_description=(
    [version]="target version of the toolchain"
)

# Options' descriptions
declare -A opts_description=(
    [url]="custom URL to be used to download the toolchain (by default toolchain is downloaded from the ARM's website deduced based on the toolchain's version)"
    [prefix]="installation prefix"
    [dirname]="name that the toolchain's dirctory should be changed to after being extracted (realative to --prefix)"
    [cleanup]="if set, the downloaded archieve will be removed after being downloaded"
)

# Helper URL
declare HELPER_SITE="https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads"
# Additional info
get_heredoc source_description <<END
    Note: 
    
        You can acquire VERSION of the toolchain to be downloaded by visiting <Source> and inspecting part 
        of the name of the toolchain between 'gcc-arm-none-eabi-' and '-<ARCHITECTURE>.<ARCHIEVE_EXTENSION>'

    Source

        [SOURCE] $HELPER_SITE
END

# ========================================================== Configuration ========================================================= #

# Logging context of the script
declare LOG_CONTEXT="arm-toochain"

# Scheme used to deduce default URL of the toolchain to be downloaded
declare DEFAULT_URL_SCHEME='https://developer.arm.com/-/media/Files/downloads/gnu-rm/$VERSION/gcc-arm-none-eabi-$VERSION-$ARCH-linux.tar.bz2'
# Download directory
declare DOWNLOAD_DIR='/tmp'

# ============================================================ Commands ============================================================ #

function install_toolchain() {

    # If no custom URL given, compose default one
    if ! is_var_set_non_empty opts[url]; then

        # Get system's architecture
        case $(get_system_arch) in
            x86_64  ) local arch=$(get_system_arch);;
            aarch64 ) local arch=$(get_system_arch);;
            *       ) log_error "Architecture's not supported ($(get_system_arch))"; exit 1;;
        esac

        # Evaluate default URL
        opts[url]=$(VERSION=${pargs[version]} ARCH=$arch eval "echo $DEFAULT_URL_SCHEME")

    fi

    # Download and extract the toolchain
    download_and_extract ${opts[url]}       \
        --arch-dir=$DOWNLOAD_DIR            \
        --extract-dir=${opts[prefix]}       \
        --show-progress                     \
        --verbose                           \
        --log-target="ARM Embedded Toolchain"

    # Rename toolchain's folder
    is_var_set_non_empty opts[dirname] &&
        mv ${opts[prefix]}/gcc-arm-none-eabi-${pargs[version]} ${opts[prefix]}/${opts[dirname]}

    # If option given, remove archieve
    is_var_set_non_empty opts[cleanup] &&
        rm $DOWNLOAD_DIR/gcc-arm-none-eabi-${pargs[version]}*.tar.bz2

    exit $?
}

# ============================================================== Main ============================================================== #

function main() {

    # Arguments
    local -A version_parg_def=( [format]="VERSION" [name]="version" [type]="s" )

    # Options
    local -A     a_url_opt_def=( [format]="-u|--url"     [name]="url"     [type]="s"               )
    local -A  b_prefix_opt_def=( [format]="--prefix"     [name]="prefix"  [type]="p" [default]="." )
    local -A c_dirname_opt_def=( [format]="--dirname"    [name]="dirname" [type]="p"               )
    local -A d_cleanup_opt_def=( [format]="-c|--cleanup" [name]="cleanup" [type]="f"               )

    # Set help generator's configuration
    ARGUMENTS_DESCRIPTION_LENGTH_MAX=120
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
    
    # Convert prefix to abspath
    opts[prefix]=$(realpath ${opts[prefix]})

    # Install toolchain
    install_toolchain

}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash

