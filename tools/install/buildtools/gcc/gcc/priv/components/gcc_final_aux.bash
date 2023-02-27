#!/usr/bin/env bash
# ====================================================================================================================================
# @file       gcc_final_aux.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 1:58:08 am
# @project    cpp-utils
# @brief      Installation routines for final GCC toolchain (auxiliary build)
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ---------------------------------------------------------------------------------------
# @brief Builds second part of the GCC compiler including support for C++ compilation
#    and gcc support library. Built files are installed into the 
#    <basedir>/install/target location. Sysroot of the
#    compiled package is set to <basedir>/install/target<toolchain_id> 
#    (e.g. <basedir>/install/target/arm-none-eabi). This way, the and c++ std library
#    are built with the `nano` version of the upstream script. Next, the upstream script
#    can copy these compiled files into the <prefix> directory and mark them as 
#    'nano-version'. 
# ---------------------------------------------------------------------------------------
function build_gcc_final_aux() {

    # ------------------------------- Prepare environment -------------------------------

    # Replace <install>/target/<toolchain-id>/usr with symbolic link to <install>/target/<toolchain-id>
    rm -f "${dirs[install_target]}/${names[toolchain_id]}/usr"
    ln -s . "${dirs[install_target]}/${names[toolchain_id]}/usr"

    # ---------------------------- Prepare predefined flags -----------------------------

    local -a CONFIG_FLAGS=()
    local -a BUILD_FLAGS=()

    # Prepare config flags
    CONFIG_FLAGS+=( "--build=${opts[build]}"                                                  )
    CONFIG_FLAGS+=( "--host=${opts[host]}"                                                    )
    CONFIG_FLAGS+=( "--target=${opts[target]}"                                                )
    CONFIG_FLAGS+=( "--prefix=${dirs[install_target]}"                                        )
    CONFIG_FLAGS+=( "--libexecdir=${dirs[prefix]}/lib"                                        )
    CONFIG_FLAGS+=( "--with-gmp=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-mpfr=${dirs[install_host]}/usr"                                   )
    CONFIG_FLAGS+=( "--with-mpc=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-isl=${dirs[install_host]}/usr"                                    )
    CONFIG_FLAGS+=( "--with-libelf=${dirs[install_host]}/usr"                                 )
    CONFIG_FLAGS+=( "--with-sysroot=${dirs[install_target]}/${names[toolchain_id]}"           )
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
    build_component 'gcc_final_aux' || return 1

}
