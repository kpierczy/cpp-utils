# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Monday, 14th March 2022 8:46:53 pm
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

# Install export
install_export(Estl)
