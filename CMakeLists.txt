# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Thursday, 3rd February 2022 10:11:45 am
# @modified Thursday, 3rd February 2022 8:31:04 pm
# @project  cpp-utils
# @brief
#    
#    Top-level CMake file of the project
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.21)

# ====================================================== Project configuration ===================================================== #

# Establish build type
set(MASTER_PROJECT OFF)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  set(MASTER_PROJECT ON)
endif()

# Project's header
project(cpp-utils VERSION 1.0 LANGUAGES CXX)

# ===================================================== Toolchain configuration ==================================================== #

if(${MASTER_PROJECT})

    # Set C++ standard for project's targets
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_CXX_EXTENSIONS True)

endif()

# ========================================================== Dependencies ========================================================== #

# Include helper scripts
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.cmake)

# Add boost::ext::* libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/boost-ext)
# Add mp-units library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/units)

# Add private targets
if(${MASTER_PROJECT})

    # Add boost headers
    add_boost_headers()

endif()

# ============================================================= Sources ============================================================ #

# Source directory
add_subdirectory(src)

# Tests directory
if(${MASTER_PROJECT})
    add_subdirectory(tests)
endif()