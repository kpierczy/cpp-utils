# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Tuesday, 15th February 2022 11:38:30 pm
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
