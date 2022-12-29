#!/usr/bin/env bash
# ====================================================================================================================================
# @file       gcc-arm-none-eabi.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 21st November 2021 6:16:17 pm
# @modified   Thursday, 29th December 2022 2:01:13 am
# @project    cpp-utils
# @brief      Installs arm-none-eabi toolchain form source (abased on the build script from ARM Embedded Toolchain v10.3-2021.10)
#    
# @copyright Krzysztof Pierczyk © 2021
# @see https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-src.tar.bz2
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

# Localiza framework utilities
export FRAMEWORK_HOME="$(dirname "$(readlink -f "$BASH_SOURCE")")"

# Source default definitions library
source $FRAMEWORK_HOME/gcc/defaults.bash
# Source helper functions
source $FRAMEWORK_HOME/gcc/helpers.bash

# ============================================================== Usage ============================================================= #

# Description of the script
declare cmd_description="Installs arm-none-eabi toolchain form source"

# Options' descriptions
declare -A opts_description=(
    [prefix]="installation directory"
    [basedir]="basedire directory for toolchain's builder"
    [verbose_tools]="if set, the building process will be run with verbose output of building tools"
    [debug]="if set, the debug build will be used"
    [autocontinue]="if set, the script will not ask user before building each next stage of toolchain"
)

# ====================================================== Common configruation ====================================================== #

# Logging context of the script
declare LOG_CONTEXT="gcc-arm-none-eabi"

# ============================================================= Helpers ============================================================ #

# ---------------------------------------------------------------------------------------
# @brief Copies newlib-nano's multilib from build to the installation directory
#
# @param src_prefix
#    prefix of the source directory
# @param dst_prefix
#    prefix of the destination directory
# @param target_gcc
#    `gcc` binary used to list multilibs
# ---------------------------------------------------------------------------------------
function copy_multi_libs() {

    # Arguments (replace spaces with '\\ ')
    local src_prefix="${1// /\\ }"
    local dst_prefix="${2// /\\ }"
    local target_gcc="${3// /\\ }"

    # Get list of multilibs
    local -a multilibs=( $("${target_gcc}" -print-multi-lib 2>/dev/null) )
    
    local multilib

    # Iterate over multilibs to be copied
    for multilib in "${multilibs[@]}" ; do

        # Compute name of the lib's directory
        local multi_dir="${multilib%%;*}"
        # Compute names of src and dst directories
        local src_dir=${src_prefix}/${multi_dir}
        local dst_dir=${dst_prefix}/${multi_dir}

        # Copy content of the lib
        cp -f "${src_dir}/libstdc++.a"  "${dst_dir}/libstdc++_nano.a"
        cp -f "${src_dir}/libsupc++.a"  "${dst_dir}/libsupc++_nano.a"
        cp -f "${src_dir}/libc.a"       "${dst_dir}/libc_nano.a"
        cp -f "${src_dir}/libg.a"       "${dst_dir}/libg_nano.a"
        cp -f "${src_dir}/librdimon.a"  "${dst_dir}/librdimon_nano.a"
        cp -f "${src_dir}/nano.specs"   "${dst_dir}/"
        cp -f "${src_dir}/rdimon.specs" "${dst_dir}/"
        cp -f "${src_dir}/nosys.specs"  "${dst_dir}/"
        cp -f "${src_dir}/"*crt0.o      "${dst_dir}/"
        
    done
}

# ============================================================== Main ============================================================== #

function install() {

    # Build version string
    declare PKG_VERSION="GNU ARM Embedded Toolchain $TOOLCHAIN_GCC_DEFAULT_VERSION"

    # ------------------------- Prepare helper configuration ----------------------------

    # Build options
    declare -a BUILD_OPTIONS=(
        "-g"
        "-O2"
    )
    # Debug build options
    is_var_set opts[debug] && {
        BUILD_OPTIONS+=( "-O0" )
    }
    # Additional build options (unused at the moment)
    false && { 
        BUILD_OPTIONS+=( "-fbracket-depth=512" )
    }

    # Helper C flags
    declare -a ENV_CFLAGS=(
        "-I${opts[basedir]}/install/host/zlib/include"
        "${BUILD_OPTIONS[@]}"
    )
    # Helper C flags
    declare -a ENV_CPPFLAGS=(
        "-I${opts[basedir]}/install/host/zlib/include"
    )
    # Helper linker flags (@note these are crucial flags passed to binutils' built;
    # thanks to them, the ld that will be used by the future build of GCC will know
    # where to look for dependecies libraries like ISL)
    declare -a ENV_LDFLAGS=(
        "-L${opts[basedir]}/install/host/zlib/lib"
        "-L${opts[basedir]}/install/host/usr/lib"
    )
    
    # Common GCC flags
    declare -a GCC_CONFIG=(
        "--with-host-libstdcxx=-static-libgcc -Wl,-Bstatic,-lstdc++,-Bdynamic -lm"
    )
    # Multilib list
    declare -a MULTILIB_LIST=(
        "--with-multilib-list=rmprofile"
    )

    # ------------------------- Prepare common configuration ----------------------------
    
    # Common compile flags
    declare -a TOOLCHAIN_COMMON_COMPILE_FLAGS=(
        "-j8"
    )

    # --------------------------- Libraries' configuration ------------------------------

    # Zlib configruation
    declare -a TOOLCHAIN_ZLIB_CONFIG_FLAGS=(
        "--static"
    )
    
    # GMP configuration
    declare -a TOOLCHAIN_GMP_CONFIG_FLAGS=(
        "--enable-cxx"
        "--disable-shared"
        "--disable-nls"
    )
    # GMP build environment
    declare -A TOOLCHAIN_GMP_BUILD_ENV=(
        ['CPPFLAGS']="-fexceptions"
    )

    # MPFR configuration
    declare -a TOOLCHAIN_MPFR_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # MPC configuration
    declare -a TOOLCHAIN_MPC_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # ISL configuration
    declare -a TOOLCHAIN_ISL_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # Elfutils (libelf) configruation
    declare -a TOOLCHAIN_ELFUTILS_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # Expat configruation
    declare -a TOOLCHAIN_EXPAT_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # Cloog configruation
    declare -a TOOLCHAIN_CLOOG_CONFIG_FLAGS=(
        "--disable-shared"
        "--disable-nls"
    )

    # --------------------------- Components configuration ------------------------------

    # Configuration of the binutils
    declare -a TOOLCHAIN_BINUTILS_CONFIG_FLAGS=(
        "--disable-nls"
        "--disable-werror"
        "--disable-sim"
        "--disable-gdb"
        "--enable-interwork"
        "--enable-plugins"
        "--with-pkgversion=$PKG_VERSION"
    )
    # Build environment of binutils
    declare -A TOOLCHAIN_BINUTILS_BUILD_ENV=(
        ['CFLAGS']="${ENV_CFLAGS[@]}"
        ['CPPFLAGS']="${ENV_CPPFLAGS[@]}"
        ['LDFLAGS']="${ENV_LDFLAGS[@]}"
    )

    # Configuration of the gcc (base build)
    declare -a TOOLCHAIN_GCC_BASE_CONFIG_FLAGS=(
        "--enable-languages=c"
        "--disable-decimal-float"
        "--disable-libffi"
        "--disable-libgomp"
        "--disable-libmudflap"
        "--disable-libquadmath"
        "--disable-libssp"
        "--disable-libstdcxx-pch"
        "--disable-nls"
        "--disable-shared"
        "--disable-threads"
        "--disable-tls"
        "--with-newlib"
        "--without-headers"
        "--with-gnu-as"
        "--with-gnu-ld"
        "--with-pkgversion=$PKG_VERSION"
        "${GCC_CONFIG[@]}"
        "${MULTILIB_LIST[@]}"
    )
    # Build environment of the gcc
    declare -A TOOLCHAIN_GCC_BASE_BUILD_ENV=(
        ['CXXFLAGS']="${BUILD_OPTIONS[@]}"
    )

    # Configuration of the libc (newlib)
    declare -a TOOLCHAIN_LIBC_CONFIG_FLAGS=(
        "--enable-newlib-io-long-long"
        "--enable-newlib-io-c99-formats"
        "--enable-newlib-reent-check-verify"
        "--enable-newlib-register-fini"
        "--enable-newlib-retargetable-locking"
        "--disable-newlib-supplied-syscalls"
        "--disable-nls"
    )
    # Build environment of libc (newlib)
    declare -A TOOLCHAIN_LIBC_BUILD_ENV=(
        ['CFLAGS_FOR_TARGET']="
            -ffunction-sections
            -fdata-sections
            -O2
        "
    )
    # Build environment of libc (newlib) [DEBUG]
    is_var_set opts[debug] &&
        TOOLCHAIN_LIBC_BUILD_ENV['CFLAGS_FOR_TARGET']+=" -g"

    # Configuration of the auxiliary libc (newlib nano)
    declare -a TOOLCHAIN_LIBC_AUX_CONFIG_FLAGS=(
        "--disable-newlib-supplied-syscalls"
        "--enable-newlib-reent-check-verify"
        "--enable-newlib-reent-small"
        "--enable-newlib-retargetable-locking"
        "--disable-newlib-fvwrite-in-streamio"
        "--disable-newlib-fseek-optimization"
        "--disable-newlib-wide-orient"
        "--enable-newlib-nano-malloc"
        "--disable-newlib-unbuf-stream-opt"
        "--enable-lite-exit"
        "--enable-newlib-global-atexit"
        "--enable-newlib-nano-formatted-io"
        "--disable-nls"
    )
    # Build environment of libc (newlib-nano)
    declare -A TOOLCHAIN_LIBC_AUX_BUILD_ENV=(
        ['CFLAGS_FOR_TARGET']="
            -ffunction-sections
            -fdata-sections
            -O2
        "
    )
    # Build environment of libc (newlib-nano) [DEBUG]
    is_var_set opts[debug] &&
        TOOLCHAIN_LIBC_AUX_BUILD_ENV['CFLAGS_FOR_TARGET']+=" -g"

    # Configuration of the GCC final build (with newlib)
    declare -a TOOLCHAIN_GCC_FINAL_CONFIG_FLAGS=(
        "--enable-languages=c,c++"
        "--enable-plugins"
        "--disable-decimal-float"
        "--disable-libffi"
        "--disable-libgomp"
        "--disable-libmudflap"
        "--disable-libquadmath"
        "--disable-libssp"
        "--disable-libstdcxx-pch"
        "--disable-nls"
        "--disable-shared"
        "--disable-threads"
        "--disable-tls"
        "--with-gnu-as"
        "--with-gnu-ld"
        "--with-newlib"
        "--with-headers=yes"
        "${GCC_CONFIG[@]}"
        "--with-pkgversion=$PKG_VERSION"
        "${MULTILIB_LIST[@]}"
    )
    # Build environment of GCC final build (with newlib) [@note Originally these flags was passed directly to `make`]
    declare -A TOOLCHAIN_GCC_FINAL_BUILD_ENV=(
        ['CXXFLAGS']="${BUILD_OPTIONS[@]}"
        ['INHIBIT_LIBC_CFLAGS']="-DUSE_TM_CLONE_REGISTRY=0"
    )

    # ----------------------------------------------------------------------
    # @note [INHIBIT_LIBC_CFLAGS] variable is set to disable transactional 
    #     memory related code in crtbegin.o. This is a workaround. Better
    #     approach is have a t-* to set this flag via CRTSTUFF_T_CFLAGS
    # ----------------------------------------------------------------------

    # Configuration of the GCC final build (with newlib-nano)
    declare -a TOOLCHAIN_GCC_FINAL_AUX_CONFIG_FLAGS=(
        "--enable-languages=c,c++"
        "--disable-decimal-float"
        "--disable-libffi"
        "--disable-libgomp"
        "--disable-libmudflap"
        "--disable-libquadmath"
        "--disable-libssp"
        "--disable-libstdcxx-pch"
        "--disable-libstdcxx-verbose"
        "--disable-nls"
        "--disable-shared"
        "--disable-threads"
        "--disable-tls"
        "--with-gnu-as"
        "--with-gnu-ld"
        "--with-newlib"
        "--with-headers=yes"
        "${GCC_CONFIG[@]}"
        "--with-pkgversion=$PKG_VERSION"
        "${MULTILIB_LIST[@]}"
    )
    # Build environment of GCC final build (with newlib-nano) [@note Originally these flags was passed directly to `make`]
    declare -A TOOLCHAIN_GCC_FINAL_AUX_BUILD_ENV=(
        ['CXXFLAGS']="${BUILD_OPTIONS[@]}"
        ['CXXFLAGS_FOR_TARGET']="
            -g
            -Os
            -ffunction-sections
            -fdata-sections
            -fno-exceptions
        "
    )
    
    # Configuration of the gdb (@note '\\\$' in --with-gdb-datadir to safely pass $ when the string is passed to `eval`)
    declare -a TOOLCHAIN_GDB_CONFIG_FLAGS=(
        "--disable-nls"
        "--disable-sim"
        "--disable-gas"
        "--disable-binutils"
        "--disable-ld"
        "--disable-gprof"
        "--with-lzma=no"
        "--with-gdb-datadir='\''\\\${prefix}'\''/arm-none-eabi/share/gdb'"
        "--with-pkgversion=$PKG_VERSION"
    )
    # Build environment of gdb
    declare -A TOOLCHAIN_GDB_BUILD_ENV=(
        ['CFLAGS']="${ENV_CFLAGS[@]}"
        ['CPPFLAGS']="${ENV_CPPFLAGS[@]}"
        ['LDFLAGS']="${ENV_LDFLAGS[@]}"
    )

    # ----------------------------------- Building --------------------------------------

    # Parse all flags
    gcc_parse_env

    local -a build_script_flags=()

    # Parse --force flag
    is_var_set opts[force] && build_script_flags+=( "--force" )
    # Parse --verbose-tools flag
    is_var_set opts[verbose_tools] && build_script_flags+=( "--verbose-tools" )
    # Parse --autocontinue flag
    is_var_set opts[autocontinue] && build_script_flags+=( "--autocontinue" )

    # Install toolchain
    $BASH_UTILS_BIN_HOME/install/buildtools/toolchain/gcc.bash                                           \
        --with-libc='newlib'                                                                             \
        --target='arm-none-eabi'                                                                         \
        --with-doc                                                                                       \
        --prefix=${opts[prefix]}                                                                         \
        --basedir=${opts[basedir]}                                                                       \
        --with-package=${opts[basedir]}/package/gcc-arm-none-eabi-$TOOLCHAIN_GCC_DEFAULT_VERSION.tar.bz2 \
        ${build_script_flags[@]}                                                                         ||
    {
        log_error "Failed to build the toolchain"
        return 1
    }
        
    # ----------------------------------- Finalize --------------------------------------

    # Get destination of the build
    local install_dir="${opts[prefix]}/gcc-arm-none-eabi-$TOOLCHAIN_GCC_DEFAULT_VERSION"

    # Copy nano's multilibs into the destination directory
    copy_multi_libs                                                    \
        src_prefix="${opts[basedir]}/install/target/arm-none-eabi/lib" \
        dst_prefix="$install_dir/arm-none-eabi/lib"                    \
        target_gcc="${opts[basedir]}/install/target/bin/arm-none-eabi-gcc"

    # Copy the nano configured `newlib.h` file into the location that `nano.specs` expects it to be
    mkdir -p "$install_dir/arm-none-eabi/include/newlib-nano"
    cp -f "${opts[basedir]}/install/target/arm-none-eabi/include/newlib.h" \
          "$install_dir/arm-none-eabi/include/newlib-nano/newlib.h"

}

# ============================================================== Main ============================================================== #

function main() {

    # Options
    local -A         a_prefix_opt_def=( [format]="--prefix"           [name]="prefix"        [type]="p" [default]="." )
    local -A        b_basedir_opt_def=( [format]="--basedir"          [name]="basedir"       [type]="p" [default]="." )
    local -A  c_verbose_tools_opt_def=( [format]='--verbose-tools'    [name]='verbose_tools' [type]='f'               )
    local -A          d_debug_opt_def=( [format]="--debug"            [name]="debug"         [type]="f"               )
    declare -A e_autocontinue_opt_def=( [format]='-y|--autocontinue'  [name]='autocontinue'  [type]='f'               )

    # Set help generator's configuration
    ARGUMENTS_DESCRIPTION_LENGTH_MAX=120
    # Parsing options
    local -a PARSEARGS_OPTS
    PARSEARGS_OPTS+=( --with-help )
    PARSEARGS_OPTS+=( --verbose   )
    
    # Parsed options
    parse_arguments
    # If help requested, return
    if [[ $ret == '5' ]]; then
        return
    elif [[ $ret != '0' ]]; then
        return $ret
    fi

    # Run installation routine
    install

}

# ============================================================= Script ============================================================= #

# Run the script
source $BASH_UTILS_HOME/lib/scripting/templates/base.bash
