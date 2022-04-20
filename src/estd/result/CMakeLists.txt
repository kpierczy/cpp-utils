# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified   Wednesday, 20th April 2022 11:20:33 pm
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

# Export and install library
install_header_library(estd-result estd-export)

