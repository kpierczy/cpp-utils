# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Thursday, 3rd February 2022 5:45:51 pm
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
add_subdirectory(concepts)
add_subdirectory(enum)
add_subdirectory(miscellaneous)
add_subdirectory(pointers)
add_subdirectory(preprocessor)
add_subdirectory(result)
add_subdirectory(strings)
add_subdirectory(traits)

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