# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified   Wednesday, 20th April 2022 11:18:30 pm
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

# Link dependancies
target_link_libraries(boost-sml-utils
    INTERFACE
        boost-sml
        estd-traits
        estd-preprocessor
        boost-headers
)

# Export and install library
install_header_library(boost-sml-utils boost-sml-utils-export)
# Install export
install_export(boost-sml-utils-export)
