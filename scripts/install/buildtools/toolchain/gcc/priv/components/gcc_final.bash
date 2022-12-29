#!/usr/bin/env bash
# ====================================================================================================================================
# @file       gcc_final.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 1:58:00 am
# @project    cpp-utils
# @brief      Installation routines for GCC final build
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ---------------------------------------------------------------------------------------
# @brief Builds second part of the GCC compiler including support for C++ compilation
#    and gcc support library. Built files are installed into the <prefix> directory.
#    Optionally builds both PDF and HTML documentation of the `binutils`. Sysroot of the
#    compiled package is set to <prefix><toolchain_id> (e.g. <prefix>/arm-none-eabi)
# ---------------------------------------------------------------------------------------
function build_gcc_final() {

    # ------------------------------- Prepare environment -------------------------------

    # Replace <prefix>/<toolchain-id>/usr with symbolic link to <prefix>/<toolchain-id>
    rm -f "${dirs[prefix]}/${names[toolchain_id]}/usr"
    ln -s . "${dirs[prefix]}/${names[toolchain_id]}/usr"

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags
    CONFIG_FLAGS+=( "--build=${opts[build]}"                                                  )
    CONFIG_FLAGS+=( "--host=${opts[host]}"                                                    )
    CONFIG_FLAGS+=( "--target=${opts[target]}"                                                )
    CONFIG_FLAGS+=( "--prefix=${dirs[prefix]}"                                                )
    CONFIG_FLAGS+=( "--libexecdir=${dirs[prefix]}/lib"                                        )
    CONFIG_FLAGS+=( "--with-gmp=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-mpfr=${dirs[install_host]}/usr"                                   )
    CONFIG_FLAGS+=( "--with-mpc=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-isl=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-libelf=${dirs[install_host]}/usr"                                 )
    CONFIG_FLAGS+=( "--with-sysroot=${dirs[prefix]}/${names[toolchain_id]}"                   )
    CONFIG_FLAGS+=( "--with-python-dir=share/${names[toolchain_base]}-${names[toolchain_id]}" )
    # Add documentation flags
    is_var_set opts[with_doc] && {
        CONFIG_FLAGS+=( "--infodir=${dirs[prefix_doc]}/info" )
        CONFIG_FLAGS+=( "--mandir=${dirs[prefix_doc]}/man"   )
        CONFIG_FLAGS+=( "--htmldir=${dirs[prefix_doc]}/html" )
        CONFIG_FLAGS+=( "--pdfdir=${dirs[prefix_doc]}/pdf"   )
    }

    # -------------------------------------- Build --------------------------------------

    # Build the library
    build_component 'gcc_final' || return 1

    # ------------------------------- Build documentation -------------------------------

    # If documentation is requrested
    if is_var_set opts[with_doc]; then
        # If documentation has not been already built (or if rebuilding is forced)
        if ! is_directory_marked ${dirs[gcc_final_build]} 'install' 'libgcc-doc' || is_var_set opts[force]; then
        
            log_info "Installing libgcc documentation..."

            # Enter build directory
            pushd ${dirs[gcc_final_build]} > /dev/null

            # Remove target marker
            remove_directory_marker ${dirs[gcc_final_build]} 'install' 'libgcc-doc'
            # Build documentation
            if is_var_set opts[verbose_tools]; then
                make install-html install-pdf
            else
                make install-html install-pdf > /dev/null
            fi
            # Mark build directory with the coresponding marker
            mark_directory ${dirs[gcc_final_build]} 'install' 'libgcc-doc'
            
            # Back to the previous location
            popd > /dev/null

            log_info "GCC-${versions[gcc_final]} documentation installed"

        # Otherwise, skip building
        else
            log_info "Skipping GCC-${versions[gcc_final]} documentation installation"
        fi
    fi

    # ------------------------------------- Cleanup -------------------------------------
    
    # Remove unused binaries
    rm -rf ${dirs[prefix]}/bin/arm-none-eabi-gccbug
    # Remove unused libiberty binaries
    rm -rf ${dirs[prefix]}/lib/libiberty.a
    for lib in $(find ${dirs[prefix]}/${names[toolchain_id]}/lib -name libiberty.a); do
        rm -rf $lib
    done
    # Remove unused include directory
    rm -rf ${dirs[prefix]}/include
    # Remove symlink created before build
    rm -rf ${dirs[prefix]}/arm-none-eabi/usr

}
