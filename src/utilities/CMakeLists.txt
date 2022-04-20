# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 20th April 2022 11:14:39 pm
# @project  Winder
# @brief
#    
#    CMakeList for project utilities' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(utilities INTERFACE)

# Callback library
add_subdirectory(callback)
# Parseargs library
add_subdirectory(parseargs)

# Link dependencies
target_link_libraries(utilities
    INTERFACE
        utilities-callback
        utilities-parseargs
)

# Export library and install export set
export_and_install(EXPORT utilities-export TARGETS utilities )
