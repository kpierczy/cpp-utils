# ====================================================================================================================================
# @file       FindSphinx.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 23rd May 2022 10:31:26 pm
# @modified   Wednesday, 28th December 2022 8:59:15 pm
# @project    cpp-utils
# @brief      Helper CMake script finding Sphinx executable
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

#Look for an executable called sphinx-build
find_program(SPHINX_EXECUTABLE
    NAMES
        sphinx-build
    DOC
        "Sphinx build utility"
)

# Add standard helper
include(FindPackageHandleStandardArgs)

# Handle standard arguments to find_package like REQUIRED and QUIET
find_package_handle_standard_args(
    Sphinx
    "Failed to find sphinx-build executable"
    SPHINX_EXECUTABLE
)
