#!/usr/bin/env bash
# ====================================================================================================================================
# @file       boost.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 1:13:17 pm
# @modified   Thursday, 29th December 2022 1:53:33 am
# @project    cpp-utils
# @brief      Script installs Boost library
#    
# @fixme
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
declare cmd_description="Installs Boost library"

# Arguments' descriptions
declare -A pargs_description=(
    [type]="type of the installation to be performed; either from apt-package or source"
    [version]="version of the boost to be installed in the 'src' variant"
    [target]="target to be installed in source variant"
)

# Options' descriptions
declare -A opts_description=(
    [prefix]="installation prefix when the 'src' variant is installed (default: .)"
    [cleanup]="if set downloaded sources will be removed after installation"
)

# Envs' descriptions
declare -A envs_description=(
    [config_flags]="array containing configruation flags to be passed to the boost's bootstrap step"
    [compile_flags]="array containing configruation flags to be passed to the boost's compilation step"
)

# Additional info
get_heredoc source_description <<END
    Source:
    
        https://sourceforge.net/projects/boost/files/boost
END

# ============================================================ Constants =========================================================== #

# Logging context of the script
declare LOG_CONTEXT="boost"

# Boost package to be installed
declare BOOST_PKG="libboost-all-dev"
# Scheme of the URL of the boost to download sources 
declare URL_SCHEME='https://sourceforge.net/projects/boost/files/boost/$version/boost_${version//./_}.tar.bz2/download'
# Boost download directory
declare DOWNLOAD_DIR="/tmp"

# ============================================================ Functions =========================================================== #

function install_pkg() {

    # Check if package already isntalled
    ! is_pkg_installed $BOOST_PKG || return

    log_info "Installing boost package ..."

    # Install package
    sudo apt update && sudo apt install -y $BOOST_PKG || {
        log_error "Failed o install $BOOST_PKG" package
        return 1
    }

    log_info "Boost package installed"
    
}

function install_source() {
    
    # Verify if boost version given
    is_var_set_non_empty pargs[version] || {
        log_error "No boost version given"
        return 1
    }

    # Evaluate the target URL
    local url=$(version=${pargs[version]} eval "echo $URL_SCHEME")

    # Compute name of the archieve
    local archieve_name=$url
    archieve_name=${archieve_name%/*}
    archieve_name=${archieve_name##*/}
    # Compute name of the directory extracted from the archieve
    local extracted_name=${archieve_name%.tar.bz2*}

    # Name of the configruation script
    local CONFIG_TOOL='bootstrap.sh'
    # Prepare configuration flags
    local -a CONFIG_FLAGS=()
    CONFIG_FLAGS+=( "--with-python=python3 "    )
    CONFIG_FLAGS+=( "--prefix=${opts[prefix]} " )
    # Add custom flags
    is_var_set envs[config_flags] && {
        local -n custom_config_flags=${envs[config_flags]}
        CONFIG_FLAGS+=( ${custom_config_flags[@]} )
    }

    # Name of the compilation script
    local BUILD_TOOL='./b2'

    # Prepare compilation target
    local -a BUILD_FLAGS=()
    case ${pargs[target]} in
        headers ) pargs[target]='headers' ;BUILD_FLAGS+=( "--prefix=${opts[prefix]}"       ) ;;
        stage   ) pargs[target]='stage'   ;BUILD_FLAGS+=( "--stagedir=${opts[prefix]}/lib" ) ;;
        full    ) pargs[target]='install' ;BUILD_FLAGS+=( "--prefix=${opts[prefix]}"       ) ;;
    esac
    # Add custom compilation flags
    is_var_set envs[compile_flags] && {
        local -n custom_compile_flags=${envs[compile_flags]}
        BUILD_FLAGS+=( "$custom_compile_flags" )
    }
    
    # Download and isntall CMake
    WGET_FLAGS='--no-clobber'                     \
    download_build_and_install $url               \
        --verbose                                 \
        --arch-path=$DOWNLOAD_DIR/$archieve_name  \
        --extract-dir=$DOWNLOAD_DIR               \
        --show-progress                           \
        --src-dir=$extracted_name                 \
        --target=${pargs[target]}                 \
        --build-dir=$DOWNLOAD_DIR/$extracted_name \
        --log-target="Boost"                      \
        --up-to=build                             \
        --force

    # If only headers have been generated, move them manually to the prefix directory
    if [[ ${pargs[target]} == "headers" ]]; then
        mkdir -p ${opts[prefix]}/include
        cp -r $DOWNLOAD_DIR/$extracted_name/boost ${opts[prefix]}/include/
    fi

    # If option given, remove archieve
    is_var_set_non_empty opts[cleanup] &&
        rm $DOWNLOAD_DIR/$extracted_name*.tar.bz2

}

# ============================================================== Main ============================================================== #

function main() {
    
    # Arguments
    local -A    a_type_parg_def=( [format]="TYPE"    [name]="type"    [type]="s" [variants]="pkg |src"                                )
    local -A b_version_parg_def=( [format]="VERSION" [name]="version" [type]="s"                                     [default]=""     )
    local -A  c_target_parg_def=( [format]="TARGET"  [name]="target"  [type]="s" [variants]="headers | stage | full" [default]="full" )

    # Options
    local -A  a_prefix_opt_def=( [format]="--prefix"     [name]="prefix"  [type]="p" [default]="." )
    local -A b_cleanup_opt_def=( [format]="-c|--cleanup" [name]="cleanup" [type]="f"               )

    # Envs
    local -A  a_config_flags_env_def=( [format]="BOOST_CONFIG_FLAGS"  [name]="config_flags"  [type]="s" )
    local -A b_compile_flags_env_def=( [format]="BOOST_COMPILE_FLAGS" [name]="compile_flags" [type]="s" )

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
    if [[ $ret == '5' ]]; then
        return
    elif [[ $ret != '0' ]]; then
        return $ret
    fi
    
    # Convert prefix to abspath
    opts[prefix]=$(realpath ${opts[prefix]})

    # Perform corresponding routine
    case ${pargs[type]} in
        'pkg' ) install_pkg    ;;
        'src' ) install_source ;;
    esac
    
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
