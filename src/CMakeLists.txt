# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Sunday, 26th June 2022 12:54:52 pm
# @project    cpp-utils
# @brief      CMakeList gathering project's targets
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Source files
add_library(${PROJECT_NAME} INTERFACE)
# Alias for the project
add_library(CppUtils ALIAS ${PROJECT_NAME})

# Subdirectories
add_subdirectory(estd)
add_subdirectory(estl)
add_subdirectory(lib-extensions)
add_subdirectory(utilities)

# Sublibraries
target_link_libraries(${PROJECT_NAME} 
    INTERFACE 
        estd
        estl
        lib-extensions
        utilities
)

# Export library and install export set
export_and_install(EXPORT ${PROJECT_NAME}-export TARGETS ${PROJECT_NAME} )
