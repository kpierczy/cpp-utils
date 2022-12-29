#!/usr/bin/env bash
# ====================================================================================================================================
# @file       cmake.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 4th November 2021 3:14:23 pm
# @modified   Thursday, 29th December 2022 2:36:45 am
# @project    cpp-utils
# @brief      Installation script for the CMake
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
declare cmd_description="Installs CMake build tools"

# Arguments' descriptions
declare -A pargs_description=(
    [type]="installation type; either installation from sources, from binary package"
    [version]="version of the CMake to be installed"
)

# Options' descriptions
declare -A opts_description=(
    [prefix]="Installation directory of the cmake (default /opt/cmake)"
    [cleanup]="if set, the downloaded archieve will be removed after being downloaded"
)

# Additional info
get_heredoc source_description <<END
    Source:
    
        https://github.com/Kitware/CMake/releases
END

# ============================================================ Constants =========================================================== #

# Logging context of the script
declare LOG_CONTEXT="cmake"

# ========================================================== Configruation ========================================================= #

# Download directory for the CMake
declare DOWNLOAD_DIR='/tmp'
# Scheme of the URL of the CMake source code
declare SRC_URL_SCHEME='https://github.com/Kitware/CMake/releases/download/v$VERSION/cmake-$VERSION.tar.gz'
# Scheme of the URL of the CMake binary variant
declare BIN_URL_SCHEME='https://github.com/Kitware/CMake/releases/download/v$VERSION/cmake-$VERSION-linux-$ARCH.tar.gz'

# ============================================================== Main ============================================================== #

function prerequisites() {

    # Create prefix folder as needed
    mkdir -p ${opts[prefix]}

    # Convert prefix to abspath
    opts[prefix]=$(realpath ${opts[prefix]})
    
}


function install_src() {

    # Evaluate the target URL
    local url=$(VERSION=${pargs[version]} eval "echo $SRC_URL_SCHEME")

    # Compute name of the directory extracted from the archieve
    local extracted_name=$url
    extracted_name=${extracted_name##*/}
    extracted_name=${extracted_name%.tar.gz}

    # Name fo the configruation script
    local CONFIG_TOOL='bootstrap'
    # Configruation flags
    local -a CONFIG_FLAGS=()
    CONFIG_FLAGS+=( "--prefix=${opts[prefix]}" )

    # Prepare utility flags
    local -a UTILITY_FLAGS=()
    is_var_set_non_empty opts[verbose] &&
        UTILITY_FLAGS+=( "--verbose-tools" )
    # Download and isntall CMake
    download_build_and_install $url ${UTILITY_FLAGS[@]} \
        --verbose                                       \
        --arch-dir=$DOWNLOAD_DIR                        \
        --extract-dir=$DOWNLOAD_DIR                     \
        --show-progress                                 \
        --src-dir=$extracted_name                       \
        --build-dir=$DOWNLOAD_DIR/$extracted_name/build \
        --log-target="CMake"                            \
        --force

    # If option given, remove archieve
    is_var_set_non_empty opts[cleanup] &&
        rm $DOWNLOAD_DIR/${extracted_name}*.tar.gz
        
}

function install_bin() {

    # Get system's architecture
    case $(get_system_arch) in
        x86_64          ) local arch='x86_64';;
        arm64 | aarch64 ) local arch='aarch64';;
        *               ) log_error "Architecture's not supported ($(get_system_arch))"; exit 1;;
    esac
    
    # Evaluate the target URL
    local url=$(VERSION=${pargs[version]} ARCH=$arch eval "echo $BIN_URL_SCHEME")
    # Compute path to the extraction directory
    local extract_path=$(basename ${opts[prefix]})
    # Compute name of the directory extracted from the archieve
    local extracted_name=$url
    extracted_name=${extracted_name##*/}
    extracted_name=${extracted_name%.tar.gz}

    # Download and extract the toolchain
    download_and_extract $url       \
        --verbose                   \
        --arch-dir=$DOWNLOAD_DIR    \
        --extract-dir=$extract_path \
        --show-progress             \
        --log-target="CMake"

    # Rename toolchain's folder
    mv $extract_path/$extracted_name ${opts[prefix]}

    # If option given, remove archieve
    is_var_set_non_empty opts[cleanup] &&
        rm $DOWNLOAD_DIR/${extracted_name}*.tar.gz

}


function install_cmake() {
    
    # Dependencies of the script
    local -a dependencies=( 
        build-essential
    )

    # Install dependencies
    install_pkg_list --allow-local-app --su -y -v -U dependencies || {
        log_error "Failed to download CMake's dependencies"
        exit 1
    }

    # Run prerequisites
    prerequisites
    # Run installation script
    case ${pargs[type]} in
        'src' ) install_src ;;
        'bin' ) install_bin ;;
    esac

}

# ============================================================== Main ============================================================== #

function main() {

    # Arguments
    local -A    a_type_parg_def=( [format]="TYPE"    [name]="type"    [type]="s" [variants]="src | bin" )
    local -A b_version_parg_def=( [format]="VERSION" [name]="version" [type]="s"                        )

    # Options
    local -A  a_prefix_opt_def=( [format]="--prefix"  [name]="prefix"      [type]="s" [default]="/opt/cmake" )
    local -A b_verbose_opt_def=( [format]="--verbose" [name]="verbose"     [type]="f"                        )
    local -A c_cleanup_opt_def=( [format]="--cleanup" [name]="cleanup"     [type]="f"                        )

    # Set help generator's configuration
    ARGUMENTS_DESCRIPTION_LENGTH_MAX=120
    # Parsing options
    declare -a PARSEARGS_OPTS
    PARSEARGS_OPTS+=( --with-help                                  )
    PARSEARGS_OPTS+=( --verbose                                    )
    PARSEARGS_OPTS+=( --with-append-description=source_description )
    
    # Parsed options
    parse_arguments
    # If help requested, return
    if [[ $ret == $PARSEARGS_HELP_REQUESTED ]]; then
        return
    elif [[ $ret != $PARSEARGS_SUCCESS ]]; then
        return $ret
    fi
    
    # Install CMake
    install_cmake
    
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
