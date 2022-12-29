#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       config.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:56:50 am
# @project    cpp-utils
# @brief      
#    
#    
# @author Lucjan Bryndza (original source: https://github.com/lucckb/isixrtos/tree/master/extras/toolchain/mac)
# @maintainer Krzysztof Pierczyk
# ====================================================================================================================================

# =========================================================== Preparation ========================================================== #

# Check if PROJECT_HOME is defined
if [ -z ${PROJECT_HOME+x} ]; then
	echo "[ERR] PROJECT_HOME is not defined. Please source sourceMe.bash script from the project's home directory."
	exit 1;
fi

# Source logging functions
source $PROJECT_HOME/scripts/aliases.bash

# ============================================================= Config ============================================================= #

# Host platform
HOST=x86_64-pc-linux-gnu

# Target to be compiled
TARGET=arm-none-eabi

# Binary basename
BASENAME="arm-none-eabi-gcc"

# Parallel build
export MAKEFLAGS="-j4"

# Library versions
BINUTILS_VER="2.36.1"
GCC_VER="11.1.0"
NEWLIB_VER="4.1.0"
GDB_VER="10.1"

# List of dependencies (homebre packages)
dependencies=(
	mpfr   # 4.1.0 version
	libmpc # 1.2.1 version
	gmp    # 6.2.1 version
	isl    # 0.24  version
	libelf # 0.8.13 version
)

# Dependencies paths
BREW_PATH="/home/linuxbrew/.linuxbrew/Cellar"
MPFR_PATH="$BREW_PATH/mpfr/4.1.0"
MPC_PATH="$BREW_PATH/libmpc/1.2.1"
GMP_PATH="$BREW_PATH/gmp/6.2.1"
ISL_PATH="$BREW_PATH/isl/0.24"
LIBELF_PATH="$BREW_PATH/libelf/0.8.13_1"

# Downloads URLs
declare -A dl_urls
dl_urls=(
	[binutils]="http://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VER.tar.gz" \
	[gccbase]="ftp://ftp.gwdg.de/pub/misc/gcc/releases/gcc-$GCC_VER/gcc-$GCC_VER.tar.gz" \
	[gcc]="ftp://ftp.gwdg.de/pub/misc/gcc/releases/gcc-$GCC_VER/gcc-$GCC_VER.tar.gz" \
	[newlib]="ftp://sourceware.org/pub/newlib/newlib-$NEWLIB_VER.tar.gz" \
	[gdb]="http://ftp.gnu.org/gnu/gdb/gdb-$GDB_VER.tar.xz" \
)

# BASE build path
BASEDIR="$PROJECT_HOME/tmp"
# Downloaddir
DLDIR="$BASEDIR/downloads"
# Build directory
BPREFIX="$BASEDIR/tbuild"
# Install directory
PREFIX="$PROJECT_HOME/tools/toolchain"
# Export directories
export PATH=$PATH:$DESTDIR/usr/local/bin:$BPREFIX


# Create array of downloaded files' names and packages' directories
declare -A dl_names
declare -A pkg_dirs
for index in ${!dl_urls[*]}
do
	name="$(basename ${dl_urls[$index]})" 
	namene=${name%.*}
	namene=${namene%.*}
	dl_names+=( [$index]="$name" )
	pkg_dirs+=( [$index]="$namene" )
done


# Sources download
download() {
	log "Num files for download: ${#dl_urls[*]}"
	for item in ${dl_urls[*]}
	do
		local bn=$(basename $item)
		if [ ! -f "$DLDIR/$bn" ]; then
			log "Downloading $bn" 
			wget -P $DLDIR $item
		fi
	done
}

# Sources unpack
unpackall() {
	for index in ${!dl_names[*]}
	do
		local item="${dl_names[$index]}" 
		local diri="${pkg_dirs[$index]}" 
		if [ ! -d "$BASEDIR/$diri" ]; then
			log "Unpacking $item ..."
			tar xf "$DLDIR/$item" -C $BASEDIR
		fi
	done
}

# Directories' building
prepare_dirs() {
	mkdir -p $DLDIR
	mkdir -p $BPREFIX
}
