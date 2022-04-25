#!/bin/bash
# ====================================================================================================================================
# @file     install_deps.bash
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 21st June 2021 1:28:12 pm
# @modified Thursday, 3rd February 2022 8:22:10 pm
# @project  mbed-utils
# @brief
#    
#    Installs dependencies of the project using Ubuntu apt repository
#    
# @usage
#
#        install_deps [MBED_CLI_VERSION]
#
#    MBED_CLI_VERSION - version of the CLI to be downloaded (either CLI_V1 or CLI_V2)
#
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source bsah-helper library
source $CPP_UTILS_HOME/extern/bash-utils/source_me.bash || {
    log_error "Failed to install project's apt dependencies"
    exit 1
}

# ============================================================ Functions =========================================================== #

main() {

    # -------------------------- Install general dependencies ---------------------------

    # Dependencies
    local -a dependencies=(
        python3-dev                # Python distribution
        build-essential            # Tests building
        manpages-dev               # Documentations' generation
        software-properties-common # APT packages management
        make                       # Projects' building
        git                        # Version control
        libncurses5                # Colorfoul logging utilities
    )

    # Install dependencies
    install_pkg_list --su -y -v dependencies || {
        log_error "Failed to install project's apt dependencies"
        exit 1
    }

}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
