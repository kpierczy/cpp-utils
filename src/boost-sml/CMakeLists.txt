# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified Thursday, 3rd February 2022 12:33:35 pm
# @project  Winder
# @brief
#    
#    CMakeList for Boost::SML utilities library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(boost-sml-utils INTERFACE)

# Include directories
target_include_directories(boost-sml-utils 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(boost-sml-utils
    INTERFACE
        sml
        estd-traits
        boost-headers
)

