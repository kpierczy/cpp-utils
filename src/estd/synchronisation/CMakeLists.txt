# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Sunday, 26th June 2022 3:30:45 pm
# @modified   Sunday, 26th June 2022 3:30:48 pm
# @project    cpp-utils
# @brief      CMakeList for synchronisation' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(estd-synchronisation INTERFACE)

# Include directories
target_include_directories(estd-synchronisation 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(estd-synchronisation estd-export)
