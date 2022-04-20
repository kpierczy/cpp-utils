# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified   Wednesday, 20th April 2022 11:18:51 pm
# @project  Winder
# @brief
#    
#    CMakeList for numeric utilities library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(numeric INTERFACE)

# Include directories
target_include_directories(numeric 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(numeric numeric-export)
# Install export
install_export(numeric-export)
