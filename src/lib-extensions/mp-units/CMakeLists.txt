# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 1st March 2023 2:32:39 am
# @project    cpp-utils
# @brief      CMakeList for units' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

find_package(mp-units CONFIG REQUIRED COMPONENTS mp-units)

# ================================================================================================================================== #

# Find dependencies
find_package(mp-units CONFIG REQUIRED)

# Source files
add_library(lib-extensions-mp-units INTERFACE)

# Include directories
target_include_directories(lib-extensions-mp-units 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(lib-extensions-mp-units
    INTERFACE
        mp-units::mp-units
        estd-traits
        estd-preprocessor
)

# Export and install library
install_header_library(lib-extensions-mp-units lib-extensions-mp-units-export)
# Install export
install_export(lib-extensions-mp-units-export)
