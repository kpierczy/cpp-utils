#!/usr/bin/env bash
# ====================================================================================================================================
# @file       defaults.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 7th November 2021 3:08:11 pm
# @modified   Thursday, 29th December 2022 1:54:25 am
# @project    cpp-utils
# @brief      Default environment variables for GCC toolchain builtool
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source helper functions
source $SCRIPT_HOME/gcc/helpers.bash

# Source prerequisites-builders
source $SCRIPT_HOME/gcc/priv/components/prerequisites.bash
# Source components-builders
source $SCRIPT_HOME/gcc/priv/components/binutils.bash
source $SCRIPT_HOME/gcc/priv/components/gcc_base.bash
source $SCRIPT_HOME/gcc/priv/components/libc.bash
source $SCRIPT_HOME/gcc/priv/components/libc_aux.bash
source $SCRIPT_HOME/gcc/priv/components/gcc_final.bash
source $SCRIPT_HOME/gcc/priv/components/gcc_final_aux.bash
source $SCRIPT_HOME/gcc/priv/components/gdb.bash
# Source build finalizer
source $SCRIPT_HOME/gcc/priv/components/finalize.bash

# ============================================================= Helpers ============================================================ #

# ---------------------------------------------------------------------------------------
# @brief Returns default version of the given @p implementation of the libc
#
# @param implementation
#     implementation to be processed (one of: {glibc, newlib, ulibc})
# @outputs
#     default version of the given @p implementation
# ---------------------------------------------------------------------------------------
function get_default_libc_version() {

    # Arguments
    local implementation="$1"

    # Return default version
    case ${implementation} in
        'glibc'                 ) echo "$TOOLCHAIN_GLIBC_DEFAULT_VERSION"  ;;
        'newlib' |'newlib-nano' ) echo "$TOOLCHAIN_NEWLIB_DEFAULT_VERSION" ;;
        'ulibc'                 ) echo "$TOOLCHAIN_ULIBC_DEFAULT_VERSION"  ;;
    esac

}

# ---------------------------------------------------------------------------------------
# @brief Returns default download URL scheme of the given @p implementation of the libc
#
# @param implementation
#     implementation to be processed (one of: {glibc, newlib, ulibc})
# @outputs
#     default download URL scheme of the given @p implementation
# ---------------------------------------------------------------------------------------
function get_default_libc_url() {

    # Arguments
    local libc_implementation="$1"

    # Return default version
    case ${libc_implementation} in
        'glibc'                 ) echo "$TOOLCHAIN_GLIBC_URL_DEFAULT_SCHEME"  ;;
        'newlib' |'newlib-nano' ) echo "$TOOLCHAIN_NEWLIB_URL_DEFAULT_SCHEME" ;;
        'ulibc'                 ) echo "$TOOLCHAIN_ULIBC_URL_DEFAULT_SCHEME"  ;;
    esac

}


# ---------------------------------------------------------------------------------------
# @brief Updates `opts` hash array with the choosen libc
# ---------------------------------------------------------------------------------------
function select_libc() {

    # Set default version of the libc and downlaod URL
    is_var_set opts[libc_version] || opts[libc_version]=$(get_default_libc_version ${opts[with_libc]})
    is_var_set opts[libc_url]     || opts[libc_url]=$(get_default_libc_url ${opts[with_libc]})
    
}

# ---------------------------------------------------------------------------------------
# @brief Installs script's dependencies
# ---------------------------------------------------------------------------------------
function install_dependencies() {

    # Enable usage of 32-bit packages
    sudo dpkg --add-architecture i386

    # Dependencies
    local -a dependencies=(

        # Copied from ARM Embedded toolchain
        software-properties-common
        build-essential
        autoconf
        autogen
        bison
        dejagnu
        flex
        flip
        gawk
        git
        gperf
        gzip
        nsis
        openssh-client
        p7zip-full
        perl
        python3-dev
        libisl-dev
        scons
        tcl
        texinfo
        tofrodos
        wget
        zip
        texlive
        texlive-extra-utils
        libncurses5-dev
        # Dependcies of 'elfutils'
        libarchive-dev
        libmicrohttpd-dev
        zstd
    )

    # Install dependencies
    install_pkg_list --su -y -v -U dependencies || {
        log_error "Could not install required dependencies"
        return 1
    }
    
}


# ---------------------------------------------------------------------------------------
# @brief Parses @var pargs[components] hash array to acquire list of components to be
#    built by the script
#
# @requires build_components
#    hash array containing names of components associated with either '1' or '0'
#    depending on whether the component needs to be built or not respectively
# ---------------------------------------------------------------------------------------
function parse_components() {

    # Prepare list of components to be built
    build_components=(
        [prerequisites]='1'
        [binutils]='0'
        [gcc_base]='0'
        [libc]='0'
        [libc_aux]='0'
        [gcc_final]='0'
        [gcc_final_aux]='0'
        [gdb]='0'
    )
    
    # If no components given enable all to be built (in such a case pargs will contain 'build_components' key)
    if is_var_set pargs[build_components]; then

        build_components[prerequisites]='1'
        build_components[binutils]='1'
        build_components[gcc_base]='1'
        build_components[libc]='1'
        build_components[libc_aux]='1'
        build_components[gcc_final]='1'
        build_components[gcc_final_aux]='1'
        build_components[gdb]='1'
        
    # Otherwise check what components should e build (in such a case pargs will contain 'build_componentsX' keys where X is one of (1, 2, ...))
    else

        # Iterate over user-given components and check which should be built
        for comp in ${pargs[@]}; do
            case $comp in

                'all' )

                    build_components[prerequisites]='1'
                    build_components[binutils]='1'
                    build_components[gcc_base]='1'
                    build_components[libc]='1'
                    build_components[libc_aux]='1'
                    build_components[gcc_final]='1'
                    build_components[gcc_final_aux]='1'
                    build_components[gdb]='1'
                    break
                    ;;

                'binutils'      ) build_components[binutils]='1'       ;;
                'gcc_base'      ) build_components[gcc_base]='1'       ;;
                'libc'          ) build_components[libc]='1'           ;;
                'libc_aux'      ) build_components[libc_aux]='1'       ;;
                'gcc_final'     ) build_components[gcc_final]='1'      ;;
                'gcc_final_aux' ) build_components[gcc_final_aux]='1'  ;;
                'gdb'           ) build_components[gdb]='1'            ;;
                
            esac
        done
    fi

}


# ---------------------------------------------------------------------------------------
# @brief Converts @p target string into the name of the associated options' set.
#   E.g. 'gcc_base' is a valid build target, but opts[*_version], opts[*_url], ...
#   options associated with it are but opts[gcc_version], opts[gcc_url], ...
# @requires versions
#    hash array containing pairs {target name}:{name with version}
# ---------------------------------------------------------------------------------------
function target_to_option_id() {

    # Arguments
    local target="$1"

    # Convert target to it's options ID
    case $target in 
        'gcc_base'      ) echo "gcc"     ;;
        'libc_aux'      ) echo "libc"    ;;
        'gcc_final'     ) echo "gcc"     ;;
        'gcc_final_aux' ) echo "gcc"     ;;
        *               ) echo "$target" ;;
    esac
    
}


# ---------------------------------------------------------------------------------------
# @brief Prepares helper hash array containing versions of targets and libraries
# @requires versions
#    hash array containing pairs {target name}:{name with version}
# ---------------------------------------------------------------------------------------
function prepare_versions() {

    local target

    # Prepare targets' versions
    for target in ${TARGETS[@]}; do

        # Get name of target-associated options identifier
        local target_opt_id=$(target_to_option_id "$target")
        # Get target's version
        versions[$target]="${opts[${target_opt_id}_version]}"
        
    done

    # Prepare toolchain's version (equal to GCC's version)
    versions[toolchain]="${opts[gcc_version]}"
    
}


# ---------------------------------------------------------------------------------------
# @brief Prepares helper hash array containing URLs of targets and libraries
# @requires urls
#    hash array containing pairs {target name}:{download urls}
# ---------------------------------------------------------------------------------------
function prepare_urls() {

    local target

    # Prepare targets' URLs
    for target in ${TARGETS[@]}; do

        # Get name of target-associated options identifier
        local target_opt_id=$(target_to_option_id "$target")

        # Evaluate download URLs with VERSION (substitute 'VERSION' with actual version)
        __LIB_VERSION_=${opts[${target_opt_id}_version]}; opts[${target_opt_id}_url]=$( echo "${opts[${target_opt_id}_url]//VERSION/$__LIB_VERSION_}" )
        # Evaluate download URLs with VERSION (substitute 'V_E_R_S_I_O_N' with actual version string where '.' are replaced with '_')
        __LIB_VERSION_=${opts[${target_opt_id}_version]//./_}; opts[${target_opt_id}_url]=$( echo "${opts[${target_opt_id}_url]//V_E_R_S_I_O_N/$__LIB_VERSION_}" )
        # Prepare target's names
        urls[${target}]="${opts[${target_opt_id}_url]}"
        
    done
    
}


# ---------------------------------------------------------------------------------------
# @brief Prepares helper hash array containing names of targets taking into account
#    versions info
#
# @requires names
#    hash array containing pairs {target name}:{name with version}
# ---------------------------------------------------------------------------------------
function prepare_names() {

    local target

    # Prepare targets' versions
    for target in ${TARGETS[@]}; do
        case $target in
            'libc'     ) names[$target]="${opts[with_libc]//_/-}-${versions[$target]}"     ;;
            'libc_aux' ) names[$target]="${opts[with_libc]//_/-}-aux-${versions[$target]}" ;;
            *          ) names[$target]="${target//_/-}-${versions[$target]}"              ;;
        esac
    done

    # Prepare toolchain's name
    names[toolchain_base]="${opts[basename]}"
    names[toolchain_id]="${opts[target]}"
    names[toolchain]="${opts[basename]}-${opts[target]}"
    
}


# ---------------------------------------------------------------------------------------
# @brief Prepares hash array containing paths to helper directories
#
# @requires dirs
#    hash array containing pairs {helper name}:{absolute path to folder}
# ---------------------------------------------------------------------------------------
function prepare_dirs() {

    # Generate abspaths
    opts[prefix]=$(to_abs_path ${opts[prefix]})
    opts[basedir]=$(to_abs_path ${opts[basedir]})

    # Change prefix directory to the toolchain-named one
    dirs[prefix]="${opts[prefix]}/${names[toolchain_base]}-${names[toolchain_id]}-${versions[toolchain]}"
    # Prepare documentation folder
    dirs[prefix_doc]="${dirs[prefix]}/share/doc/${opts[basename]}-${opts[target]}"
    # Prepare paths to helper directories
    dirs[basedir]="${opts[basedir]}"
    dirs[download]="${opts[basedir]}/download"
    dirs[package]="${opts[basedir]}/package"
    dirs[src]="${opts[basedir]}/src"
    dirs[build]="${opts[basedir]}/build"
    dirs[install]="${opts[basedir]}/install"
    dirs[install_host]="${opts[basedir]}/install/host"
    dirs[install_target]="${opts[basedir]}/install/target"

    # Make target directory
    mkdir -p ${dirs[prefix]}
    mkdir -p ${dirs[prefix_doc]}
    # Create helper directories
    mkdir -p ${dirs[download]}
    mkdir -p ${dirs[src]}
    mkdir -p ${dirs[build]}
    mkdir -p ${dirs[install]}
    mkdir -p ${dirs[install_host]}
    mkdir -p ${dirs[install_target]}

    local target

    # Prepare targets' build directories
    for target in ${TARGETS[@]}; do
        dirs[${target}_build]="${dirs[build]}/${names[${target}]}"
    done

}


# ---------------------------------------------------------------------------------------
# @brief Prepares helper hash array containing paths to source archieves associated 
#    with targets
#
# @requires archieves
#    hash array containing pairs {target name}:{path to the source archieve}
# ---------------------------------------------------------------------------------------
function prepare_archieves() {

    local target

    # Prepare targets' versions
    for target in ${TARGETS[@]}; do

        # Get name of target-associated options identifier
        local target_opt_id=$(target_to_option_id "$target")
        # Get target's archieve's path
        case $target in
            'libc' | 'libc_aux'                        ) archieves[$target]="${dirs[download]}/${opts[with_libc]}-${versions[$target]}" ;;
            'gcc_base' | 'gcc_final' | 'gcc_final_aux' ) archieves[$target]="${dirs[download]}/gcc-${versions[$target]}"                ;;            
            *                                          ) archieves[$target]="${dirs[download]}/${target_opt_id}-${versions[$target]}"   ;;
        esac
        # Get target's src directory
        dirs[${target}_src]="${dirs[src]}/$(basename ${archieves[$target]})"

    done
    
}

# ---------------------------------------------------------------------------------------
# @brief Prepares helper hash array containing user-defined flags given for components'
#    configuration/compilation
#
# @requires config_flags
#    hash array containing pairs {target name}:{config_flags}
# @requires compile_flags
#    hash array containing pairs {target name}:{compile_flags}
# @requires build_env
#    hash array containing pairs {target name}:{build_env}
# ---------------------------------------------------------------------------------------
function prepare_flags() {

    local target

    # Get common flags
    config_flags[common]=${envs[common_config_flags]}
    compile_flags[common]=${envs[common_compile_flags]}
    build_env[common]=${envs[common_build_env]}

    # Prepare targets' flag sets
    for target in ${TARGETS[@]}; do

        # Get name of target-associated options identifier
        local target_opt_id=$(target_to_option_id "$target")
        # Get target's flags
        config_flags[$target]=${envs[${target}_config_flags]}
        compile_flags[$target]=${envs[${target}_compile_flags]}
        build_env[$target]=${envs[${target}_build_env]}
        
    done
    
}

# ---------------------------------------------------------------------------------------
# @brief Compiles comma-separated list of components to be build by the script
#
# @requires components
#    hash array containing names of components associated with either '1' or '0'
#    depending on whether the component needs to be built or not respectively
#
# @outputs
#     compiled list
# ---------------------------------------------------------------------------------------
function get_components_list() {

    # Initialize output
    local result=""

    local comp

    # Iterate over components
    for comp in ${COMPONENTS[@]}; do
        if [[ ${build_components[$comp]} == '1' ]]; then
            result+="$comp, "
        fi
    done
    
    # Remove trailing comma
    if [[ ${#result} != "0" ]]; then
        result=${result::-2}
    fi

    # Output result
    echo $result
}


# ---------------------------------------------------------------------------------------
# @brief Prints summary of the build to be conducted to the user
# ---------------------------------------------------------------------------------------
function print_build_info() {

    local comp

    # Print list of components to be built
    log_info "Building: $(set_bold)$(get_components_list)$(reset_colors)"
    # Print folders info
    log_info "Installation directory: $(set_bold)${dirs[prefix]}$(reset_colors)"
    log_info "Working directory: $(set_bold)${dirs[basedir]}$(reset_colors)"

    # Print versions info
    log info "Versions:"
    # Print dependencies' versions
    [[ ${build_components[prerequisites]} == '1' ]] && {
        log info "    - dependencies:"
        log info "        - zlib: $(set_bold)$(set_fblue)${versions[zlib]}$(reset_colors)"
        log info "        - gmp: $(set_bold)$(set_fblue)${versions[gmp]}$(reset_colors)"
        log info "        - mpfr: $(set_bold)$(set_fblue)${versions[mpfr]}$(reset_colors)"
        log info "        - mpc: $(set_bold)$(set_fblue)${versions[mpc]}$(reset_colors)"
        log info "        - isl: $(set_bold)$(set_fblue)${versions[isl]}$(reset_colors)"
        log info "        - elfutils: $(set_bold)$(set_fblue)${versions[elfutils]}$(reset_colors)"
        log info "        - expat: $(set_bold)$(set_fblue)${versions[expat]}$(reset_colors)"
        log info "        - cloog: $(set_bold)$(set_fblue)${versions[cloog]}$(reset_colors)"
    }
    # Print components versions
    [[ ${build_components[binutils]}      != '1' ]] || log info "    - binutils: $(set_bold)$(set_fgreen)${versions[binutils]}$(reset_colors)"
    [[ ${build_components[gcc_base]}      != '1' ]] ||
    [[ ${build_components[gcc_final]}     != '1' ]] ||
    [[ ${build_components[gcc_final_aux]} != '1' ]] || log info "    - gcc: $(set_bold)$(set_fgreen)${versions[gcc_base]}$(reset_colors)"
    [[ ${build_components[libc]}          != '1' ]] ||
    [[ ${build_components[libc_aux]}      != '1' ]] || log info "    - ${opts[with_libc]}: $(set_bold)$(set_fgreen)${versions[libc]}$(reset_colors)"
    [[ ${build_components[gdb]}           != '1' ]] || log info "    - gdb: $(set_bold)$(set_fgreen)${versions[gdb]}$(reset_colors)"

    # Prin whether build is forced
    is_var_set opts[force] &&
        log_info "Build type: $(set_bold)$(set_blue)forced$(reset_colors)" ||
        log_info "Build type: $(set_bold)default$(reset_colors)"
    # Prin whether documentation is built
    is_var_set opts[with_doc] &&
        log_info "Building documentation: $(set_bold)$(set_fblue)yes$(reset_colors)" ||
        log_info "Building documentation: $(set_bold)no$(reset_colors)"

    log_info
}

# ---------------------------------------------------------------------------------------
# @brief Helper predicate function selecting environmental variables required for the 
#    build
# 
# @returns
#   @retval @c 0 if variable is not needed
#   @retval @c 1 otherwise
# ---------------------------------------------------------------------------------------
function is_variable_useless_for_build() {

    # Arguments
    local var="$1"

    # Choose variables to keep
    case "$var" in

        # 1st category [2]
        WORKSPACE | SRC_VERSION ) return 1 ;;
        # 2nd category [2]
        DEJAGNU | DISPLAY | HOME | LD_LIBRARY_PATH | LOGNAME | PATH | PWD | SHELL | SHLVL | TERM | USER | USERNAME | XAUTHORITY ) return 1 ;;
        # 3rd category [2]
        com.apple.* ) return 1 ;;
        # 4th category [2]
        LSB_* | LSF_* | LS_* | EGO_* | HOSTTYPE | TMPDIR ) return 1 ;;
        # Others (discard)
        * ) return 0 ;;
        
    esac

}

# ========================================================= Implementation ========================================================= #

function install() {

    # Helper dictionaries
    declare -A build_components
    declare -A versions
    declare -A urls
    declare -A names
    declare -A dirs
    declare -A archieves
    # Flags sets
    declare -A config_flags
    declare -A compile_flags
    declare -A build_env

    # Set default version of the libc and downlaod URL
    select_libc
    # Install script's dependencies
    install_dependencies
    # Parse list of components to be built
    parse_components

    # Evaluate `eval` string to possibly inject some entities into the script's namespace
    eval "${envs[eval_string]}"

    # Parse versions strings
    prepare_versions
    # Parse download URLs
    prepare_urls
    # Prepare helper names
    prepare_names
    # Create required directories
    prepare_dirs
    # Create required paths to source archieves
    prepare_archieves
    # Parse custom compilation/ocnfiguration flags
    prepare_flags

    # Print build informations
    print_build_info
    # Clear environment
    clean_env 'is_variable_useless_for_build'
    
    local component
    
    # Build subsequent components
    for component in ${COMPONENTS[@]}; do

        # Check if component is to be built
        if [[ ${build_components[$component]} == '1' ]]; then

            # Compute component's name (change '_' to '-')
            local component_name=${component//_/-}

            # Wait for user's confirmation to build the next component
            is_var_set opts[autocontinue] || {
                log_info "$(set_bold)Press a key to start building of the $(set_fgreen)$component_name$(reset_colors)"; read -s
            }

            log_info "Building $component_name..."

            # Get name of the corresponding function
            local build_cmd="build_$component"
            # Build component
            $build_cmd && ret=$? || ret=$?
            
            # Verify result of building
            if [[ "$ret" != "0" ]]; then
                log_error "Failed to build $component_name"
                return 1
            else
                log_info "$(set_bold)$(set_fgreen)${component_name^}$(set_fdefault) built$(reset_colors)"
            fi
        
        fi
        
    done

    # Wait for user's confirmation to build the next component
    is_var_set opts[autocontinue] || {
        log_info "$(set_bold)Press a key to start build's finalizing$(reset_colors)"; read -s
    }

    log_info "Finalizing toolchain build..."
    
    # Finalize build
    build_finalize && ret=$? || ret=$?

    # Verify result of building
    if [[ "$ret" != "0" ]]; then
        log_error "Failed to finalize toolchain build"
        return 1
    else
        log_info "Toolchain built sucesfully"
    fi
}
