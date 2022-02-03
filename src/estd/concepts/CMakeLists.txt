# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:06 pm
# @modified Thursday, 3rd February 2022 5:46:19 pm
# @project  cpp-tools
# @brief
#    
#    CMakeList for concepts' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-concepts INTERFACE)

# Include directories
target_include_directories(estd-concepts 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
