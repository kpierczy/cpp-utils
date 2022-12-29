#!/usr/bin/env bash
# ====================================================================================================================================
# @file       finalize.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Saturday, 6th November 2021 5:49:03 pm
# @modified   Thursday, 29th December 2022 1:58:26 am
# @project    cpp-utils
# @brief      Routines finalizing toolchain's build
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ============================================================= Helpers ============================================================ #

# ---------------------------------------------------------------------------------------
# @brief Strip binary files as in "strip binary" form
# 
# @param bin
#    name of the binary
# ---------------------------------------------------------------------------------------
function strip_binary() {
    
    # Arguments
    local bin="$1"

    # Check type of the given file
    file $bin | grep -q -e "\bELF\b" -e "\bPE\b" -e "\bPE32\b" -e "\bMach-O\b"
    # If one of the supported types given, strip
    if [ $? -eq 0 ]; then
        strip $bin 2>/dev/null || true
    fi

}

# ========================================================= Implementation ========================================================= #

# ---------------------------------------------------------------------------------------
# @brief Finalizes build of the GCC toolchain by:
#
#     - cleaning up the installation directory  
#     - stripping host's binary objects (on non-debug builds)
#     - stripping target's binary objects (on non-debug builds)
#     - packaging buitl toolchain into the archieve (if requested)
# 
# ---------------------------------------------------------------------------------------
function build_finalize() {

    # ------------------------------------- Cleanup -------------------------------------

    # If cleanup not been already conducted (or if rebuilding is forced)
    if ! is_directory_marked ${dirs[build]} 'build' 'cleanup' || is_var_set opts[force]; then

        log_info "Cleaning installation directory..."

        # Remove target marker
        remove_directory_marker ${dirs[build]} 'build' 'cleanup'
        # Pretidy build by removing unused files
        rm -rf "${dirs[prefix]}/lib/libiberty.a"
        find "${dirs[prefix]}" -name '*.la' -exec rm '{}' ';'
        # Mark build directory with the coresponding marker
        mark_directory ${dirs[build]} 'build' 'cleanup'

        log_info "Installation directory cleaned"

    fi

    # --------------------------------- Strip binaries ----------------------------------

    # Strip built obejct in release builds
    if is_var_set opts[debug]; then

        # If binaries not been already stripped (or if rebuilding is forced)
        if ! is_directory_marked ${dirs[build]} 'build' 'strip' || is_var_set opts[force]; then

            # Remove target marker
            remove_directory_marker ${dirs[build]} 'build' 'strip'

            log_info "Stripping host binaries..."

            # Strip tolchain's binaries in 'bin' subfolder
            for bin in $(find ${dirs[prefix]}/bin/ -name ${names[toolchain_id]}-\*); do
                strip_binary $bin
            done
            # Strip tolchain's binaries in '<toolchain-id>/bin' subfolder
            for bin in $(find ${dirs[prefix]}/${names[toolchain_id]}/bin/ -maxdepth 1 -mindepth 1 -name \*); do
                strip_binary $bin
            done
            # Strip tolchain's binaries in 'lib/gcc/<toolchain-id>/<version>' subfolder
            for bin in $(find ${dirs[prefix]}/lib/gcc/${names[toolchain_id]}/${versions[gcc]}/ -maxdepth 1 -name \* -perm /111 -and ! -type d); do
                strip_binary $bin
            done

            log_info "Host binaries stripped"
            log_info "Stripping target binaries..."

            # Clear helper stack to put envs on
            clear_env_stack
            # Add compiled GCC's binaries to path
            prepend_path_env_stack ${dirs[prefix]}/bin
            
            local target_lib

            # Symbols to strip
            local sym_to_strip
            sym_to_strip+=" -R .comment"
            sym_to_strip+=" -R .note"
            sym_to_strip+=" -R .debug_info"
            sym_to_strip+=" -R .debug_aranges"
            sym_to_strip+=" -R .debug_pubnames"
            sym_to_strip+=" -R .debug_pubtypes"
            sym_to_strip+=" -R .debug_abbrev"
            sym_to_strip+=" -R .debug_line"
            sym_to_strip+=" -R .debug_str"
            sym_to_strip+=" -R .debug_ranges"
            sym_to_strip+=" -R .debug_loc"

            # Strip static libraries
            for target_lib in $(find ${dirs[prefix]}/${names[toolchain_id]}/lib -name \*.a); do
                ${names[toolchain_id]}-objcopy \
                    $sym_to_strip              \
                    $target_lib                \
                || true
            done
            # Strip objects
            for target_obj in $(find ${dirs[prefix]}/${names[toolchain_id]}/lib -name \*.o); do
                ${names[toolchain_id]}-objcopy \
                    $sym_to_strip              \
                    $target_lib                \
                || true
            done
            # Strip libgcc static libraries
            for target_lib in $(find ${dirs[prefix]}/lib/gcc/${names[toolchain_id]}/${versions[gcc]} -name \*.a); do
                ${names[toolchain_id]}-objcopy \
                    $sym_to_strip              \
                    $target_lib                \
                || true
            done
            # Strip libgcc objects
            for target_obj in $(find ${dirs[prefix]}/lib/gcc/${names[toolchain_id]}/${versions[gcc]} -name \*.o); do
                ${names[toolchain_id]}-objcopy \
                    $sym_to_strip              \
                    $target_lib                \
                || true
            done

            # Restore environment
            restore_env_stack

            log_info "Target binaries stripped"
            
            # Mark build directory with the coresponding marker
            mark_directory ${dirs[build]} 'build' 'strip'

        fi

    fi

    # --------------------------------- Create package ----------------------------------

    # Create package archieve, if requested
    if is_var_set opts[with_package]; then

        log_info "Building toolchain package"

        # Remove package if already exists
        rm -f ${opts[with_package]}
        # Create directory for package
        mkdir -p $(dirname ${opts[with_package]})

        # Enter build directory
        pushd ${dirs[build]} > /dev/null
        # Create symbolic link to installation dir
        mkdir -p ${dirs[package]}
        ln -s ${dirs[prefix]} ${dirs[package]}/$(basename ${dirs[prefix]})
        
        # Make the package tarball
        tar cjf ${opts[with_package]}                            \
            --exclude="host-${opts[host]}"                                        \
            "${dirs[package]}/$(basename ${dirs[prefix]})/${names[toolchain_id]}" \
            "${dirs[package]}/$(basename ${dirs[prefix]})/bin"                    \
            "${dirs[package]}/$(basename ${dirs[prefix]})/lib"                    \
            "${dirs[package]}/$(basename ${dirs[prefix]})/share"

        # Remove symlink and temporary directory
        rm -f ${dirs[package]}/$(basename ${dirs[prefix]})
        # Restore directory
        popd

        log_info "Package built"
        
    fi
    
}
