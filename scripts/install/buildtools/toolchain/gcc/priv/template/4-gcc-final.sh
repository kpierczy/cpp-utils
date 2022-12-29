#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       4-gccfinal.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:55:57 am
# @project    cpp-utils
# @brief      Script building `newlib` component of the toolchain
#    
# @author Lucjan Bryndza (original source: https://github.com/lucckb/isixrtos/tree/master/extras/toolchain/mac)
# @maintainer Krzysztof Pierczyk
# ====================================================================================================================================

# Source config file
source $PROJECT_HOME/scripts/toolchain/config.bash

# Component's name
compname="$BASEDIR/${pkg_dirs[gcc]}"

# # Patching sources
# if [ ! -f "$compname/.patched" ]; then
#  	patch -p2 -d "$BASEDIR/${pkg_dirs[gcc]}" < patch-gcc-config-arm-t-arm-elf.diff
#  	touch "$compname/.patched"
# fi

# Compile component
if [ ! -f "$compname/.compile-full" ]; then
	pushd "$BASEDIR"
	mkdir -p build-gcc && cd build-gcc
	../${pkg_dirs[gcc]}/configure \
		--target=$TARGET \
		--prefix=$PREFIX \
		--build=$HOST \
		--host=$HOST \
		--with-as=${PREFIX}/bin/${TARGET}-as \
		--with-ld=${PREFIX}/bin/${TARGET}-ld \
		--with-mpfr=/usr/local/Cellar/mpfr/4.1.0 \
		--with-mpc=/usr/local/Cellar/libmpc/1.2.1 \
		--with-gmp=/usr/local/Cellar/gmp/6.2.1 \
		--with-isl=/usr/local/Cellar/isl/0.24 \
		--with-libelf=/usr/local/Cellar/libelf/0.8.13_1 \
		--enable-languages=c,c++ \
        --enable-plugins \
        --disable-decimal-float \
        --disable-libffi \
        --disable-libgomp \
        --disable-libmudflap \
        --disable-libquadmath \
        --disable-libssp \
        --disable-libstdcxx-pch \
        --disable-nls \
        --disable-shared \
        --disable-threads \
        --disable-tls \
        --with-gnu-as \
        --with-gnu-ld \
        --with-newlib \
        --with-headers=yes \
		--with-multilib-list=rmprofile  

	make -j $(nproc) INHIBIT_LIBC_CFLAGS="-DUSE_TM_CLONE_REGISTRY=0"
	popd
	touch "$compname/.compile-full" 
fi

# Install component
if [ ! -f "$compname/.installed-full" ]; then
	pushd "$BASEDIR"
	cd build-gcc
	make install
	popd
	touch "$compname/.installed-full" 
fi

