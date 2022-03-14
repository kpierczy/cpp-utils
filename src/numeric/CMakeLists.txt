# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified Monday, 14th March 2022 8:47:31 pm
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
install_header_library(numeric Numeric)
# Install export
install_export(Numeric)
