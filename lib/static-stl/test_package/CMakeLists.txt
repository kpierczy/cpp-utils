# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Friday, 16th December 2022 1:50:50 am
# @modified   Thursday, 29th December 2022 2:02:57 am
# @project    cpp-utils
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(static-stl CONFIG REQUIRED)

# Compile simple application
add_executable(test src/test.cpp)
# Link it with the tested library
target_link_libraries(test static-stl::static-stl)
