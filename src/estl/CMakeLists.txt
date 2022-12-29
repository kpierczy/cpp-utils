# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Thursday, 29th December 2022 4:55:32 am
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

# Require C++20 standard
target_compile_features(estl INTERFACE cxx_std_20)

# Export library and install export set
export_and_install(EXPORT estl-export TARGETS estl )
