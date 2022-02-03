# ====================================================================================================================================
# @file     uits.bash
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 29th November 2021 10:34:15 am
# @modified Thursday, 3rd February 2022 8:22:10 pm
# @project  mbed-utils
# @brief
#    
#    Script installing 'units' library for C++
#    
# @source https://github.com/mpusz/units
# @fixme
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source bsah-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash

# Log context
LOG_CONTEXT="units-lib"

# ============================================================ Functions =========================================================== #

main() {

    # Check if library is already installed
    if [[ -f $CPP_UTILS_HOME/lib/gsl-lite/lib/cmake/gsl-lite/gsl-lite-config.cmake ]] &&
       [[ -f $CPP_UTILS_HOME/lib/fmt/lib/cmake/fmt/fmt-config.cmake ]] 
    then
        exit 0
    fi

    # ----------------------------------- Download dependencies -----------------------------------

    # prepare list of repositories to be downloaded
    local DEP_HOME="${CPP_UTILS_HOME}/extern/units/extern"
    local -a repos=( gsl_lite_repo fmt_repo )
    local -A gsl_lite_repo=( [path]="${DEP_HOME}/gsl-lite" [url]="https://github.com/gsl-lite/gsl-lite" [tag]="v0.38.1" )
    local -A      fmt_repo=( [path]="${DEP_HOME}/fmt"      [url]="https://github.com/fmtlib/fmt"        [tag]="8.0.1"   )
    # Prepare list of git flags to be used
    local -a GIT_CUSTOM_FLAGS=( "--recursive" )

    # Downloaded dependencies, if required
    if [[ ! -d ${gsl_lite_repo[path]} ]] ||
       [[ ! -d ${fmt_repo[path]}      ]]
    then
    
        log_info "Downloading dependencies of the units library"

        # Download repositories
        GIT_FLAGS=GIT_CUSTOM_FLAGS git_clone_list -v -p repos || {
            log_error "Failed to download dependencies of the units library"
            exit 1
        }

        log_info "Dependencies downloaded"

    fi

    # ----------------------------------- Install dependencies ------------------------------------

    # Enter repository where dependencies have been downloaded
    pushd $CPP_UTILS_HOME/extern/units/extern > /dev/null

    # Additional configuration flags for dependencies library
    local -a DEPS_CMAKE_CONFIG_FLAGS=(
        "-DCMAKE_BUILD_TYPE:STRING=Release"
        "-DCMAKE_TOOLCHAIN_FILE:PATH=$CPP_UTILS_HOME/cmake/toolchain.cmake"
        "-DFMT_TEST:BOOL=FALSE" # fmt library
    )

    # Install gsl-lite depenency
    if [[ ! -f $CPP_UTILS_HOME/lib/gsl-lite/lib/cmake/gsl-lite/gsl-lite-config.cmake ]]; then
        CMAKE_CONFIG_FLAGS=DEPS_CMAKE_CONFIG_FLAGS      \
        cmake_build_install                             \
            --src-dir=gsl-lite                          \
            --install-dir=$CPP_UTILS_HOME/lib/gsl-lite \
            --log-target="gsl-lite library"             \
            --verbose                                   \
        || { popd > /dev/null;  exit 1; }
    fi

    # Install fmt depenency
    if [[ ! -f $CPP_UTILS_HOME/lib/fmt/lib/cmake/fmt/fmt-config.cmake ]]; then
        CMAKE_CONFIG_FLAGS=DEPS_CMAKE_CONFIG_FLAGS \
        cmake_build_install                        \
            --src-dir=fmt                          \
            --install-dir=$CPP_UTILS_HOME/lib/fmt \
            --log-target="fmt library"             \
            --verbose                              \
        || { popd > /dev/null;  exit 1; }
        
    fi

    # ---------------------- Modify incorrect parts of the units' CMake tree ----------------------

    # -----------------------------------------------------------------------------------
    # Run over all CMakeLists.txt files in the `units` tree and change 'gsl-lite::gsl-lite'
    # target to 'gsl::gsl-lite' as the package changes naming convention in the meantime
    # -----------------------------------------------------------------------------------
    enable_word_splitting
    for file in $(find $CPP_UTILS_HOME/extern/units -name "CMakeLists.txt"); do
        sed -i 's/gsl-lite::gsl-lite/gsl::gsl-lite/g' "$file" || {
            log_error "Failed to modify CMakeLists.txt files of the units library"
             popd > /dev/null
             exit 1
        }
    done
    disable_word_splitting
    
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
