#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       config.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:56:10 am
# @project    cpp-utils
# @brief      Script building `gdb` component of the toolchain
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
	compname="$BASEDIR/${pkg_dirs[gdb]}"
	
	# Compile component
	if [ ! -f "$compname/.compiled" ]; then
		pushd $BASEDIR
		mkdir -p build-gdb && cd build-gdb
		$compname/configure \
			--target=$TARGET \
			--prefix=$PREFIX \
			--build=$HOST \
			--host=$HOST \
			--disable-nls \
			--enable-interwork \
			--enable-multilib \
			--with-float=soft  \
			--disable-shared \
			--disable-libgomp \
			--disable-libmudflap \
			--disable-libssp \
			--disable-werror \
			--enable-lto \
			--without-auto-load-safe-path \
			--with-guile=no \
			--with-readline=/usr/local/Cellar/readline/8.1 \
			--with-libelf=/usr/local/Cellar/libelf/0.8.13_1
		make
		popd
		touch "$compname/.compiled" 
	fi

	# Install component
	if [ ! -f "$compname/.installed" ]; then
		pushd $BASEDIR
		cd build-gdb
		sudo make install
		popd
		touch "$compname/.installed" 
	fi
}

# ============================================================= Script ============================================================= #

build
