# ====================================================================================================================================
# @file       common.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 24th May 2022 4:43:28 pm
# @modified   Thursday, 4th August 2022 7:33:06 pm
# @project    cpp-utils
# @brief      Definition of helper macros utilized by the packahe
#    
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Add cmake dircetory to path, to use find_package(Sphinx)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/doc" ${CMAKE_MODULE_PATH})

# ============================================================ Helpers ============================================================= #

# ----------------------------------------------------------------------------------
# @brief If variable named @p var is not set, sets it to the @p default value
# ----------------------------------------------------------------------------------
macro(set_default var default)
    if(NOT ${var})
        set(${var} ${default})
    endif()
endmacro()

# ----------------------------------------------------------------------------------
# @brief If variable named @p var_in is not set, sets variable named @p var_out to 
#    the @p default value; otherwise sets it to the value of @p var_in
# ----------------------------------------------------------------------------------
macro(parse_with_default var_in default var_out)
    if(NOT ${var_in})
        set(${var_out} ${default})
    else()
        set(${var_out} ${${var_in}})
    endif()
endmacro()

# ----------------------------------------------------------------------------------
# @brief Creates variable named @p arg . If variable named ${ARG_PREFIX}_${arg} is 
#    not set, sets created variable to the @p default value . Otherwise, sets it
#    to the value of the ${ARG_PREFIX}_${arg} variable
# ----------------------------------------------------------------------------------
macro(parse_arg arg default)
    parse_with_default(${ARG_PREFIX}_${arg} ${default} ${arg})
endmacro()

# ----------------------------------------------------------------------------------
# @brief If variable named ${ARG_PREFIX}_${arg} is set, sets variable named @p arg
#    to it's value. Otherwise, leaves value named @p arg unset
# ----------------------------------------------------------------------------------
macro(strip_arg arg)
    if(${ARG_PREFIX}_${arg})
        set(${arg} ${${ARG_PREFIX}_${arg}})
    endif()
endmacro()