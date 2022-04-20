# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 20th April 2022 11:16:07 pm
# @project  Winder
# @brief
#    
#    CMakeList for project patterns' library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(patterns INTERFACE)

# CPRT pattern
add_subdirectory(cprt)

# Link dependencies
target_link_libraries(patterns
    INTERFACE
        patterns-cprt
)

# Export library and install export set
export_and_install(EXPORT patterns-export TARGETS patterns )

