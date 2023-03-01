# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th February 2022 11:26:49 pm
# @modified   Wednesday, 1st March 2023 2:10:33 am
# @project    cpp-utils
# @brief      CMakeList for namedtuple' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(estl-namedtuple INTERFACE)

# Include directories
target_include_directories(estl-namedtuple 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependencies
target_link_libraries(estl-namedtuple
    INTERFACE
        estd-string
)

# Export and install library
install_header_library(estl-namedtuple estl-export)

