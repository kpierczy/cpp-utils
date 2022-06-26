# ====================================================================================================================================
# @file       find_packages.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 12th May 2022 11:27:46 pm
# @modified   Tuesday, 24th May 2022 8:53:39 pm
# @project    engineering-thesis
# @brief      Definition of the find_packages() macros family
#    
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ----------------------------------------------------------------------------------
# @brief Calls find_package(... REQUIRED) for each package in the arguments list
# ----------------------------------------------------------------------------------
macro(find_packages)
    foreach(package ${ARGN})
        find_package(${package} REQUIRED)
    endforeach()
endmacro()
