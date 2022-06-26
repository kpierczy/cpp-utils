# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 15th June 2021 9:10:08 pm
# @modified   Sunday, 26th June 2022 12:51:50 pm
# @project    cpp-utils
# @brief      CMakeList for numeric utilities library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(utilities-numeric INTERFACE)

# Include directories
target_include_directories(utilities-numeric 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(utilities-numeric utilities-numeric-export)
# Install export
install_export(utilities-numeric-export)
