# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified Monday, 14th March 2022 7:04:51 pm
# @project  Winder
# @brief
#    
#    CMakeList for generic action's result library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-result INTERFACE)

# Include directories
target_include_directories(estd-result 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(estd-result
    INTERFACE
        estd-enum
)
