# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Monday, 14th March 2022 8:56:14 pm
# @project  Winder
# @brief
#    
#    CMakeList gathering project's targets
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_library(${PROJECT_NAME} INTERFACE)
# Alias for the project
add_library(CppUtils ALIAS ${PROJECT_NAME})

# Subdirectories
add_subdirectory(boost-sml)
add_subdirectory(estd)
add_subdirectory(estl)
add_subdirectory(numeric)
add_subdirectory(patterns)
add_subdirectory(units)
add_subdirectory(utilities)

# Sublibraries
target_link_libraries(${PROJECT_NAME} 
    INTERFACE 
        boost-sml
        estd
        estl
        numeric
        patterns
        units
        utilities
)
