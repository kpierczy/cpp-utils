#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       3-newlib.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:55:42 am
# @project    cpp-utils
# @brief      Script building `newlib` component of the toolchain
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
	compname="$BASEDIR/${pkg_dirs[newlib]}"

	# Compile component
	if [ ! -f "$compname/.compiled" ]; then
		echo "Compile binutils..."
		pushd $compname
		./configure \
			--target=$TARGET \
			--prefix=$PREFIX \
			--build=$HOST \
			--host=$HOST \
			--disable-newlib-supplied-syscalls    \
			--enable-newlib-reent-check-verify    \
			--enable-newlib-reent-small           \
			--enable-newlib-retargetable-locking  \
			--disable-newlib-fvwrite-in-streamio  \
			--disable-newlib-fseek-optimization   \
			--disable-newlib-wide-orient          \
			--enable-newlib-nano-malloc           \
			--disable-newlib-unbuf-stream-opt     \
			--enable-lite-exit                    \
			--enable-newlib-global-atexit         \
			--enable-newlib-nano-formatted-io     \
			--disable-nls
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

build
