# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Monday, 14th March 2022 8:44:01 pm
# @project  Winder
# @brief
#    
#    CMakeList for preprocessor library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-preprocessor INTERFACE)

# Include directories
target_include_directories(estd-preprocessor 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(estd-preprocessor
    INTERFACE
        boost-headers
)

# Export and install library
install_header_library(estd-preprocessor Estd)
