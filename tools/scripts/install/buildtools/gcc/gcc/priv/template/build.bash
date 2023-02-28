#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       build.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 22nd July 2021 7:08:01 pm
# @modified   Thursday, 29th December 2022 1:56:39 am
# @project    cpp-utils
# @brief      Building script for GCC tolchain
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ========================================================== Preparations ========================================================== #

# Check if PROJECT_HOME is defined
if [ -z ${PROJECT_HOME+x} ]; then
	echo "[ERR] PROJECT_HOME is not defined. Please source sourceMe.bash script from the project's home directory."
	exit 1;
fi

# Source config file
source $PROJECT_HOME/scripts/toolchain/config.bash

# ========================================================== Dependencies ========================================================== #

# Check if Homebrew is installed
if ! which brew > /dev/null; then
	warn "Homebrew is not installed"
	$PROJECT_PATH/scripts/install/install_homebrew.bash
fi

# Install dependencies
log "Installing toolchain's dependencies..."
install_with_brew "${dependencies[@]}"
log "Dependencies installed"

# # Make symbolic link for libisl
# if [[ ! -e /usr/local/lib/libisl.so.23 ]]; then
# 	log "creating link"
# 	sudo ln -s $ISL_PATH/lib/libisl.so.23 /usr/local/lib/libisl.so.23
# fi

# ============================================================ Building ============================================================ #

# Components to be built
components=(
	"1-binutils.sh"
	"2-gccbase.sh"
	"3-newlib.sh"
	"4-gcc-final.sh"
	"5-gdb.sh"
)

# Build binutils
for component in "${components[@]}"; do

	# Get component's name
	name="${component:2:-3}"

	# Wait for user's confirmation to build the next component
	log "Press a key to start building of the $name"; read
	log "Building $name ..."
	# Build component
	$PROJECT_HOME/scripts/toolchain/$component
	# Verify result of building
	if [[ "$?" != "0" ]]; then
		err "$name failed to build"
		exit 1
	else
		log "$name built"
	fi
done
