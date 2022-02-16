# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 14th February 2022 11:26:49 pm
# @modified Tuesday, 15th February 2022 11:38:53 pm
# @project  cpp-utils
# @brief
#    
#    CMakeList for circular buffer' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(patterns-cprt INTERFACE)

# Include directories
target_include_directories(patterns-cprt 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
