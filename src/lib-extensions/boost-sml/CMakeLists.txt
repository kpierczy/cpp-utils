# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 15th June 2021 9:10:08 pm
# @modified   Sunday, 26th June 2022 3:50:41 pm
# @project    cpp-utils
# @brief      CMakeList for Boost::SML utilities library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(lib-extensions-boost-sml INTERFACE)

# Include directories
target_include_directories(lib-extensions-boost-sml 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
)

# Link dependancies
target_link_libraries(lib-extensions-boost-sml
    INTERFACE
        Boost::sml
        estd-traits
        estd-preprocessor
)

# Export and install library
install_header_library(lib-extensions-boost-sml lib-extensions-boost-sml-export)
# Install export
install_export(lib-extensions-boost-sml-export)
