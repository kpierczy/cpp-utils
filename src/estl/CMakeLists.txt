# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 20th April 2022 11:18:01 pm
# @project  Winder
# @brief
#    
#    CMakeList for project extended-stl' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(estl INTERFACE)

# Circular buffer implementation
add_subdirectory(circular_buffer)
# Named tuple implementation
add_subdirectory(namedtuple)

# Link dependencies
target_link_libraries(estl
    INTERFACE
        estl-circular-buffer
        estl-namedtuple
)

# Export library and install export set
export_and_install(EXPORT estl-export TARGETS estl )
