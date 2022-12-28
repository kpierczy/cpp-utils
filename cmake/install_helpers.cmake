# ====================================================================================================================================
# @file     install_helpers.cmake
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 14th March 2022 8:17:49 pm
# @modified   Wednesday, 28th December 2022 8:59:15 pm
# @project  cpp-utils
# @brief
#    
#    Helper CMake functions for installing libraries
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================ Includes ============================================================ #

include(CMakeParseArguments)

# ============================================================ Functions =========================================================== #

# ---------------------------------------------------------------------------------------
# @brief Helper macro defining an export set for given targets
# ---------------------------------------------------------------------------------------
function(export_targets)

    # Arguments
    cmake_parse_arguments(PARSE_ARGV 0 "ARG" "" "EXPORT" "TARGETS")

    # Export targets
    install(
        TARGETS 
            ${ARG_TARGETS}
        EXPORT
            ${ARG_EXPORT}
    )

endfunction()

# ---------------------------------------------------------------------------------------
# @brief Helper macro function installing the header-only library with its exports
# ---------------------------------------------------------------------------------------
function(install_header_library target export)

    # Arguments
    cmake_parse_arguments(PARSE_ARGV 2 "ARG" "" "" "")

    # Add alias to the library
    add_library(cpp-utils::${target} ALIAS ${target})

    # Export library
    export_targets(TARGETS ${target} EXPORT ${export})
    # Install headers
    install(
        DIRECTORY
            ${CMAKE_CURRENT_LIST_DIR}/include/
        DESTINATION
            include
    )

endfunction()

# ---------------------------------------------------------------------------------------
# @brief Helper macro function installing exports
# ---------------------------------------------------------------------------------------
function(install_export export)

    # Arguments
    cmake_parse_arguments(PARSE_ARGV 1 "ARG" "" "" "")

    # Install export
    install(EXPORT ${export}
        FILE
            ${export}Targets.cmake
        NAMESPACE
            cpp-utils::
        DESTINATION
            lib/cmake/cpp-utils-${PROJECT_VERSION}
    )

endfunction()

# ---------------------------------------------------------------------------------------
# @brief Helper macro function installing exports
# ---------------------------------------------------------------------------------------
function(export_and_install)

    # Arguments
    cmake_parse_arguments(PARSE_ARGV 0 "ARG" "" "EXPORT" "TARGETS")

    # Export targets
    export_targets(EXPORT ${ARG_EXPORT} TARGETS ${ARG_TARGETS})
    # Install export
    install_export(${ARG_EXPORT})

endfunction()