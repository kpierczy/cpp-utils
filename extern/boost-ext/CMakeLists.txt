# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 1st December 2021 10:21:39 am
# @modified Thursday, 3rd February 2022 12:33:08 pm
# @project    Winder
# @brief
#    
#    CMake file for local fork of the boost-extensions libraries
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Add subdirectories
add_subdirectory(di)
add_subdirectory(sml)
add_subdirectory(ut)

# Add interface target
add_library(boost-extensions INTERFACE)
# Add libraries to the compiled target
target_link_libraries(boost-extensions
    INTERFACE
        di
        sml
        ut
)
