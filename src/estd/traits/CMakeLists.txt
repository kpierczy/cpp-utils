# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Monday, 14th March 2022 9:19:38 pm
# @project  Winder
# @brief
#    
#    CMakeList for traits' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-traits INTERFACE)

# Include directories
target_include_directories(estd-traits 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Export and install library
install_header_library(estd-traits Estd)
