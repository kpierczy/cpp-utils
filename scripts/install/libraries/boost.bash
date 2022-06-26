# ====================================================================================================================================
# @file       boost.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 29th November 2021 5:31:52 pm
# @modified   Sunday, 26th June 2022 2:00:23 pm
# @project    Winder
# @brief      Script installing boost headers
#
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Log context
LOG_CONTEXT="boost"

# Source bsah-helper library
source $BASH_UTILS_HOME/source_me.bash

# ============================================================ Functions =========================================================== #

main() {

    # If boost installation is not needed, exit
    if [[ $CPP_UTILS_INSTALL_BOOST_HEADERS != true ]]; then
        exit 0
    fi

    # Boost home
    local BOOST_DIR=$CPP_UTILS_HOME/extern/boost
    # Installation directory
    local BOOST_INSTALL_DIR=$CPP_UTILS_HOME/src/boost-headers

    # Check if library is already installed
    if [[ -f $BOOST_INSTALL_DIR/.installed ]]; then
        exit 0
    fi

    # Create target repository
    mkdir -p $BOOST_INSTALL_DIR/include
    
    log_info "Installing boost headers to $BOOST_INSTALL_DIR..."
    cd $BOOST_DIR

    # Bootstrap the repository
    ./bootstrap.sh --prefix=$BOOST_INSTALL_DIR || {
        log_error "Failed to bootstrap the library"
        exit 1
    }
    # Install headers
    ./b2 headers --prefix=$BOOST_INSTALL_DIR || {
        log_error "Failed to install headers"
        exit 1
    }
    # Move installed headers (resolve symlinks)
    cp -RL $BOOST_DIR/boost $BOOST_INSTALL_DIR/include/boost
    # Remove original headers installation
    rm -rf $BOOST_DIR/b2
    rm -rf $BOOST_DIR/bin.v2
    rm -rf $BOOST_DIR/boost

    # Mark that the library has been installed
    touch $BOOST_INSTALL_DIR/.installed || {
        log_warning "Library has been installed, but the marker could not be created." \
                    "The next reun of the script will result in reinstalling headers"
    }
    # Add CMake file for the boost-headers target
    echo "include(\${CMAKE_SOURCE_DIR}/cmake/boost.cmake)" >  $BOOST_INSTALL_DIR/CMakeLists.txt
    echo "add_boost_headers()"                             >> $BOOST_INSTALL_DIR/CMakeLists.txt
    # Add gitignore file to boost sources
    echo "*" > $BOOST_INSTALL_DIR/.gitignore

    log_info "Boost headers installed"
}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
