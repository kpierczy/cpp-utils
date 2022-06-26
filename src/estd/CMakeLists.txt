# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 3:09:47 pm
# @project    cpp-utils
# @brief      CMakeList for project extended-std' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(estd INTERFACE)

# Subdirectories
add_subdirectory(bits)
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
        estd-bits
        estd-concepts
        estd-enum
        estd-miscellaneous
        estd-pointers
        estd-preprocessor
        estd-result
        estd-strings
        estd-traits
)

# Export library and install export set
export_and_install(EXPORT estd-export TARGETS estd )

