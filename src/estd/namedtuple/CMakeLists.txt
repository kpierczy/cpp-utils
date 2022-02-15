# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 14th February 2022 11:26:49 pm
# @modified Monday, 14th February 2022 11:27:00 pm
# @project  cpp-utils
# @brief
#    
#    CMakeList for namedtuple' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-namedtuple INTERFACE)

# Include directories
target_include_directories(estd-namedtuple 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
