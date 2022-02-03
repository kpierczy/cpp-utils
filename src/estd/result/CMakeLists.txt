# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Tuesday, 15th June 2021 9:10:08 pm
# @modified Thursday, 3rd February 2022 5:49:20 pm
# @project  Winder
# @brief
#    
#    CMakeList for generic action's result library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd-result
    src/default_domain_impl.cpp
)

# Include directories
target_include_directories(estd-result 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependancies
target_link_libraries(estd-result
    PUBLIC
        estd-enum
)
