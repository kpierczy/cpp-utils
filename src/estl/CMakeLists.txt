# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 11:49:16 am
# @project    cpp-utils
# @brief      CMakeList for project extended-stl' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
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
