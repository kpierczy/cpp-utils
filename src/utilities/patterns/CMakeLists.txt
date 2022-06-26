# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 12:51:57 pm
# @project    cpp-utils
# @brief      CMakeList for project patterns' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(utilities-patterns INTERFACE)

# CPRT pattern
add_subdirectory(crtp)

# Link dependencies
target_link_libraries(utilities-patterns
    INTERFACE
        utilities-patterns-crtp
)

# Export library and install export set
export_and_install(EXPORT utilities-patterns-export TARGETS utilities-patterns )

