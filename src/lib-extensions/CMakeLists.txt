# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 12:52:56 pm
# @project    cpp-utils
# @brief      CMakeList for project extended-std' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(lib-extensions INTERFACE)

# Subdirectories
add_subdirectory(boost-sml)
add_subdirectory(mp-units)

# Sublibraries
target_link_libraries(lib-extensions
    INTERFACE 
        lib-extensions-boost-sml
        lib-extensions-mp-units
)

# Export library and install export set
export_and_install(EXPORT lib-extensions-export TARGETS lib-extensions )

