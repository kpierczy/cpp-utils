# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th February 2022 11:26:49 pm
# @modified   Sunday, 26th June 2022 11:49:16 am
# @project    cpp-utils
# @brief      CMakeList for circular buffer' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(estl-circular-buffer INTERFACE)

# Include directories
target_include_directories(estl-circular-buffer 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(estl-circular-buffer estl-export)
