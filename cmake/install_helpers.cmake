# ====================================================================================================================================
# @file     install_helpers.cmake
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 14th March 2022 8:17:49 pm
# @modified Monday, 14th March 2022 9:46:08 pm
# @project  engineering-thesis
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
# @brief Helper macro function installing the header-only library with its exports
# ---------------------------------------------------------------------------------------
function(install_header_library target export)

    # Arguments
    cmake_parse_arguments(PARSE_ARGV 2 "ARG" "" "" "")

    # Add alias to the library
    add_library(cpp-utils::${target} ALIAS ${target})

    # Export library
    install(TARGETS ${target} EXPORT ${export})
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