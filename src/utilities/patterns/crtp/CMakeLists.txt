# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th February 2022 11:26:49 pm
# @modified   Sunday, 26th June 2022 12:52:09 pm
# @project    cpp-utils
# @brief      CMakeList for CRTP pattern library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(utilities-patterns-crtp INTERFACE)

# Include directories
target_include_directories(utilities-patterns-crtp 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(utilities-patterns-crtp utilities-patterns-export)
