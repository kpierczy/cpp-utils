# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 20th April 2022 11:15:52 pm
# @project  Winder
# @brief
#    
#    CMakeList for units' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(units INTERFACE)

# Include directories
target_include_directories(units 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(units
    INTERFACE
        mp-units
        estd-traits
        estd-preprocessor
)

# Export and install library
install_header_library(units units-export)
# Install export
install_export(units-export)
