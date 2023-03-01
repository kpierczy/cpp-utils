# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 1st March 2023 2:15:59 am
# @project    cpp-utils
# @brief      CMakeList for project utilities' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(utilities INTERFACE)

add_subdirectory(callback)
add_subdirectory(numeric)
add_subdirectory(patterns)

# Link dependencies
target_link_libraries(utilities
    INTERFACE
        utilities-callback
        utilities-numeric
        utilities-patterns
)

# Require C++20 standard
target_compile_features(utilities INTERFACE cxx_std_20)

# Export library and install export set
export_and_install(EXPORT utilities-export TARGETS utilities )
