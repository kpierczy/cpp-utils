#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       1-binutils.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:54:45 am
# @project    cpp-utils
# @brief      Script building `binutils` component of the toolchain
#    
# @author Lucjan Bryndza (original source: https://github.com/lucckb/isixrtos/tree/master/extras/toolchain/mac)
# @maintainer Krzysztof Pierczyk
# ====================================================================================================================================

# Source config file
source $PROJECT_HOME/scripts/toolchain/config.bash

# =========================================================== Definitions ========================================================== #

# Building function
build() {
	
	# Component's name
	compname="$BASEDIR/${pkg_dirs[binutils]}"
	
	# Compile component
	if [ ! -f "$compname/.compiled" ]; then
		pushd $compname
		./configure \
			--target=$TARGET \
			--prefix=$PREFIX \
			--build=$HOST \
			--host=$HOST \
			--disable-nls \
			--disable-werror \
			--disable-sim \
			--disable-gdb \
			--enable-interwork \
			--enable-plugins 

		make
		popd
		touch "$compname/.compiled" 
	fi
	# Install component
	if [ ! -f "$compname/.installed" ]; then
		pushd $compname
		make install
		popd
		touch "$compname/.installed" 
	fi
}

# ============================================================= Script ============================================================= #

prepare_dirs
download
unpackall
build
