#!/bin/bash
# ====================================================================================================================================
# @file       dependencies.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 21st June 2021 1:28:12 pm
# @modified   Thursday, 29th December 2022 1:53:30 am
# @project    cpp-utils
# @brief      Installs dependencies of the project using Ubuntu apt repository
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
