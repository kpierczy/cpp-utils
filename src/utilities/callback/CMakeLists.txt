# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Monday, 14th March 2022 8:49:00 pm
# @project  Winder
# @brief
#    
#    CMakeList for project callback' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(utilities-callback INTERFACE)

# Include directories
target_include_directories(utilities-callback 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(utilities-callback
    INTERFACE
        estd-concepts
)

# Export and install library
install_header_library(utilities-callback Utilities)
