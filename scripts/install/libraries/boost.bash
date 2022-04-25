# ====================================================================================================================================
# @file       boost.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 29th November 2021 5:31:52 pm
# @modified Thursday, 3rd February 2022 8:22:10 pm
# @project    Winder
# @brief
#    
#    Script installing boost headers
#
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Log context
LOG_CONTEXT="boost"

# Source bsah-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash || {
    log_error "Failed to install boost library"
    exit 1
}

# ============================================================ Functions =========================================================== #

main() {

    # Check if library is already installed
    if [[ -f $CPP_UTILS_HOME/extern/boost/.installed ]]; then
        exit 0
    fi

    # -------------------------------------- Install library --------------------------------------

    # Boost home
    local BOOST_DIR=$CPP_UTILS_HOME/extern/boost
    # Installation directory
    local BOOST_INSTALL_DIR=$BOOST_DIR/boost

    log_info "Installing boost headers to $BOOST_INSTALL_DIR..."
    pushd $BOOST_DIR > /dev/null

    # Bootstrap the repository
    ./bootstrap.sh --prefix=$BOOST_INSTALL_DIR || {
        log_error "Failed to bootstrap the library"
        return 1
    }
    # Install headers
    ./b2 headers || {
        log_error "Failed to install headers"
        return 1
    }
    # Mark that the library has been installed
    touch .installed || {
        log_warning "Library has been installed, but the marker could not be created." \
                    "The next reun of the script will result in reinstalling headers"
    }

    popd > /dev/null
    log_info "Boost headers installed"
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
