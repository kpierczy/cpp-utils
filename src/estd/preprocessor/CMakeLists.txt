# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 1st March 2023 3:18:09 am
# @project    cpp-utils
# @brief      CMakeList for preprocessor library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

find_package(Boost CONFIG REQUIRED)

# ================================================================================================================================== #

# Source files
add_library(estd-preprocessor INTERFACE)

# Include directories
target_include_directories(estd-preprocessor 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Linke dependencies
target_link_libraries(estd-preprocessor
    INTERFACE
        Boost::headers
)

# Export and install library
install_header_library(estd-preprocessor estd-export)
