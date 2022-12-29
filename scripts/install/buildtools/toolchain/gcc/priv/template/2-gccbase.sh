#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       2-gccbase.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:55:23 am
# @project    cpp-utils
# @brief      Script building `GCC` (base components) component of the toolchain
#    
# @author Lucjan Bryndza (original source: https://github.com/lucckb/isixrtos/tree/master/extras/toolchain/mac)
# @maintainer Krzysztof Pierczyk
# ====================================================================================================================================

# Source config file
source $PROJECT_HOME/scripts/toolchain/config.bash

# Component's name
compname="$BASEDIR/${pkg_dirs[gccbase]}"

# Compile component
if [ ! -f "$compname/.compile-base" ]; then
	pushd "$BASEDIR"
	mkdir -p base-gcc && cd base-gcc
	$compname/configure \
	--target=$TARGET \
	--prefix=$PREFIX \
	--build=$HOST \
	--host=$HOST \
	--with-as=${PREFIX}/bin/${TARGET}-as \
	--with-ld=${PREFIX}/bin/${TARGET}-ld \
	--with-mpfr=$MPFR_PATH \
	--with-mpc=$MPC_PATH \
	--with-gmp=$GMP_PATH \
	--with-isl-lib=$ISL_PATH/lib \
	--with-isl-include=$ISL_PATH/include \
	--with-libelf=$LIBELF_PATH \
 	--enable-languages=c \
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
    --with-newlib \
    --without-headers \
    --with-gnu-as \
    --with-gnu-ld \
	--with-multilib-list=rmprofile  

	make all-gcc 
	popd
	touch "$compname/.compile-base" 
fi

# Install component
if [ ! -f "$compname/.installed-base" ]; then
	pushd "$BASEDIR"
	cd base-gcc
	make install-gcc
	popd
	touch "$compname/.installed-base" 
fi

