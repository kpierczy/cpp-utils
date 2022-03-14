# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Monday, 14th February 2022 11:26:49 pm
# @modified Monday, 14th March 2022 8:45:26 pm
# @project  cpp-utils
# @brief
#    
#    CMakeList for namedtuple' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estl-namedtuple INTERFACE)

# Include directories
target_include_directories(estl-namedtuple 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(estl-namedtuple Estl)

