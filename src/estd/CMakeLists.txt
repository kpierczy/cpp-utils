# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Thursday, 3rd February 2022 2:59:56 pm
# @project  Winder
# @brief
#    
#    CMakeList for project extended-std' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estd INTERFACE)

# Subdirectories
add_subdirectory(estd-concepts)
add_subdirectory(estd-enum)
add_subdirectory(estd-miscellaneous)
add_subdirectory(estd-pointers)
add_subdirectory(estd-preprocessor)
add_subdirectory(estd-result)
add_subdirectory(estd-strings)
add_subdirectory(estd-traits)

# Sublibraries
target_link_libraries(estd 
    INTERFACE 
        estd-concepts
        estd-enum
        estd-miscellaneous
        estd-pointers
        estd-preprocessor
        estd-result
        estd-strings
        estd-traits
)
