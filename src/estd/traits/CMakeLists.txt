# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 3:51:03 pm
# @project    cpp-utils
# @brief      CMakeList for traits' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(estd-traits INTERFACE)

# Include directories
target_include_directories(estd-traits 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
)

# Export and install library
install_header_library(estd-traits estd-export)
