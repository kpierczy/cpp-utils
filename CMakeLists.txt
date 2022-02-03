# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Thursday, 3rd February 2022 10:11:45 am
# @modified Thursday, 3rd February 2022 10:20:08 am
# @project  cpp-utils
# @brief
#    
#    Top-level CMake file of the project
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.21)

# ====================================================== Project configuration ===================================================== #

# Project's header
project(cpp-utils VERSION 1.0 LANGUAGES CXX)

# ===================================================== Toolchain configuration ==================================================== #

# Set C++ standard for project's targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS True)

# ============================================================= Sources ============================================================ #

# Source directory
add_subdirectory(src)
