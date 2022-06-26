# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 15th June 2021 9:10:08 pm
# @modified   Sunday, 26th June 2022 1:53:17 pm
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
)

# Link dependancies
target_link_libraries(lib-extensions-boost-sml
    INTERFACE
        boost-sml
        estd-traits
        estd-preprocessor
        ${Boost_INCLUDE_DIRS}
)

# Export and install library
install_header_library(lib-extensions-boost-sml lib-extensions-boost-sml-export)
# Install export
install_export(lib-extensions-boost-sml-export)
