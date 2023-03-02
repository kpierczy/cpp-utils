#!/usr/bin/env bash
# ====================================================================================================================================
# @file       binutils.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Friday, 3rd March 2023 12:10:18 am
# @project    cpp-utils
# @brief      Installation routines for `binutils` toolset
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ---------------------------------------------------------------------------------------
# @brief Builds `binutils` components of the toolchain and installs into the <prefix>
#   directory. Optionally builds both PDF and HTML documentation of the `binutils`.
#   Sysroot of the compiled package is set to <prefix><toolchain_id> (e.g. <prefix>/
#   arm-none-eabi)
# ---------------------------------------------------------------------------------------
function build_binutils() {

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags
    CONFIG_FLAGS+=( "--build=${opts[build]}"                                )
    CONFIG_FLAGS+=( "--host=${opts[host]}"                                  )
    CONFIG_FLAGS+=( "--target=${opts[target]}"                              )
    CONFIG_FLAGS+=( "--prefix=${dirs[prefix]}"                              )
    CONFIG_FLAGS+=( "--with-sysroot=${dirs[prefix]}/${names[toolchain_id]}" )
    # Add documentation flags
    is_var_set opts[with_doc] && {
        CONFIG_FLAGS+=( "--infodir=${dirs[prefix_doc]}/info" )
        CONFIG_FLAGS+=( "--mandir=${dirs[prefix_doc]}/man"   )
        CONFIG_FLAGS+=( "--htmldir=${dirs[prefix_doc]}/html" )
        CONFIG_FLAGS+=( "--pdfdir=${dirs[prefix_doc]}/pdf"   )
    }

    # -------------------------------------- Build --------------------------------------

    # Build the library
    build_component 'binutils' || return 1

    # ------------------------------- Build documentation -------------------------------

    # If documentation is requrested
    if is_var_set opts[with_doc]; then
        # If documentation has not been already built (or if rebuilding is forced)
        if ! is_directory_marked ${dirs[binutils_build]} 'install' 'doc' || is_var_set opts[force]; then

            log_info "Installing binutils documentation..."

            # Enter build directory
            pushd ${dirs[binutils_build]} > /dev/null

            # Remove target marker
            remove_directory_marker ${dirs[binutils_build]} 'install' 'doc'
            # Build documentation
            if is_var_set opts[verbose_tools]; then
                make install-html install-pdf
            else
                make install-html install-pdf > /dev/null
            fi
            # Mark build directory with the coresponding marker
            mark_directory ${dirs[binutils_build]} 'install' 'doc'

            # Back to the previous location
            popd > /dev/null

            log_info "${names[binutils]^} documentation installed"

        # Otherwise, skip building
        else
            log_info "Skipping ${names[binutils]} documentation installation"
        fi
    fi

    # ------------------------------------ Finalize -------------------------------------

    # Copy <prefix> content to target's installation directory for future use
    # (these binutils will be used by final-GCC that is built with --with-sysroot
    # pointing to the target's installation directory, i.e. when bulding gcc_final_aux
    # usually used for building optimised version of libc++)
    deep_copy_dir ${dirs[prefix]} ${dirs[install_target]}

    # ------------------------------------- Cleanup -------------------------------------
    
    # Remove library folder from prefix directory (useless)
    rm -rf ${dirs[prefix]}/lib

    # @note At the moment, every run of the binutils' building script results in
    # deleting <prefix>/lib folder. This results in need of reinstalling further
    # components. This can be fixed by providing --shoft-archieve-extraction
    # flag to the `download_build_and_install` function that stops re-extraction
    # when one with the target name already exists so that binutil's archieve is
    # not re-extracted every time. Then `download_build_and_install` could return
    # @c 2 status code when skipping all actions and only on @c <prefix>/lib dir
    # directory would be deleted. As a temproary workaround remove .installed
    # markers of other components on every run ( @fixme )
    rm -f ${dirs[gcc_base_build]}/.installed
    rm -f ${dirs[libc_build]}/.installed
    rm -f ${dirs[libc_aux_build]}/.installed
    rm -f ${dirs[gcc_final_build]}/.installed
    rm -f ${dirs[gcc_final_aux_build]}/.installed
    rm -f ${dirs[gdb_build]}/.installed

}

