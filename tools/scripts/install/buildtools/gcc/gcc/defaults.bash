#!/usr/bin/env bash
# ====================================================================================================================================
# @file       defaults.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 7th November 2021 3:08:11 pm
# @modified   Thursday, 29th December 2022 1:54:18 am
# @project    cpp-utils
# @brief      Default environment variables for GCC toolchain builtool
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Components' version (defaults)
var_set_default TOOLCHAIN_BINUTILS_DEFAULT_VERSION "2.37"
var_set_default TOOLCHAIN_GCC_DEFAULT_VERSION      "11.2.0"
var_set_default TOOLCHAIN_GLIBC_DEFAULT_VERSION    "2.34"
var_set_default TOOLCHAIN_NEWLIB_DEFAULT_VERSION   "4.1.0"
var_set_default TOOLCHAIN_ULIBC_DEFAULT_VERSION    "0.9.33.2"
var_set_default TOOLCHAIN_GDB_DEFAULT_VERSION      "11.1"
# Version of libraries
var_set_default TOOLCHAIN_ZLIB_DEFAULT_VERSION     "1.2.11"
var_set_default TOOLCHAIN_GMP_DEFAULT_VERSION      "6.2.1"
var_set_default TOOLCHAIN_MPFR_DEFAULT_VERSION     "4.1.0"
var_set_default TOOLCHAIN_MPC_DEFAULT_VERSION      "1.2.1"
var_set_default TOOLCHAIN_ISL_DEFAULT_VERSION      "0.18"
var_set_default TOOLCHAIN_ELFUTILS_DEFAULT_VERSION "0.186"
var_set_default TOOLCHAIN_EXPAT_DEFAULT_VERSION    "2.4.6"
var_set_default TOOLCHAIN_CLOOG_DEFAULT_VERSION    "0.18.1"

# Download links for components
var_set_default TOOLCHAIN_BINUTILS_URL_DEFAULT_SCHEME "https://ftp.gnu.org/gnu/binutils/binutils-VERSION.tar.gz"
var_set_default TOOLCHAIN_GCC_URL_DEFAULT_SCHEME      "https://ftp.gnu.org/gnu/gcc/gcc-VERSION/gcc-VERSION.tar.gz"
var_set_default TOOLCHAIN_GLIBC_URL_DEFAULT_SCHEME    "https://ftp.gnu.org/gnu/glibc/glibc-VERSION.tar.gz"
var_set_default TOOLCHAIN_NEWLIB_URL_DEFAULT_SCHEME   "ftp://sourceware.org/pub/newlib/newlib-VERSION.tar.gz"
var_set_default TOOLCHAIN_ULIBC_URL_DEFAULT_SCHEME    "https://www.uclibc.org/downloads/uClibc-VERSION.tar.bz2"
var_set_default TOOLCHAIN_GDB_URL_DEFAULT_SCHEME      "https://ftp.gnu.org/gnu/gdb/gdb-VERSION.tar.gz"
# Download links for libraries
var_set_default TOOLCHAIN_ZLIB_URL_DEFAULT_SCHEME     "https://zlib.net/zlib-VERSION.tar.gz"
var_set_default TOOLCHAIN_GMP_URL_DEFAULT_SCHEME      "https://ftp.gnu.org/gnu/gmp/gmp-VERSION.tar.bz2"
var_set_default TOOLCHAIN_MPFR_URL_DEFAULT_SCHEME     "https://ftp.gnu.org/gnu/mpfr/mpfr-VERSION.tar.gz"
var_set_default TOOLCHAIN_MPC_URL_DEFAULT_SCHEME      "https://ftp.gnu.org/gnu/mpc/mpc-VERSION.tar.gz"
var_set_default TOOLCHAIN_ISL_URL_DEFAULT_SCHEME      "https://gcc.gnu.org/pub/gcc/infrastructure/isl-VERSION.tar.bz2"
var_set_default TOOLCHAIN_ELFUTILS_URL_DEFAULT_SCHEME "https://sourceware.org/elfutils/ftp/VERSION/elfutils-VERSION.tar.bz2"
var_set_default TOOLCHAIN_EXPAT_URL_DEFAULT_SCHEME    "https://github.com/libexpat/libexpat/releases/download/R_V_E_R_S_I_O_N/expat-VERSION.tar.gz"
var_set_default TOOLCHAIN_CLOOG_URL_DEFAULT_SCHEME    "https://gcc.gnu.org/pub/gcc/infrastructure/cloog-VERSION.tar.gz"

# Empty environment hash-array
declare -A EMPTY_ENV=()
