# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 3rd February 2022 10:11:45 am
# @modified   Tuesday, 28th February 2023 2:41:30 pm
# @project    cpp-utils
# @brief      Top-level CMake file of the project
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.16)

# ====================================================== Project configuration ===================================================== #

# Establish build type
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(MASTER_PROJECT ON)
else()
    set(MASTER_PROJECT OFF)
endif()

# Project's header
project(cpp-utils VERSION 1.1.0 LANGUAGES CXX)

# ============================================================= Options ============================================================ #

option(WITH_TESTS "If ON builds tests" OFF)

# ============================================================ Includes ============================================================ #

include(CTest)
include(CMakePackageConfigHelpers)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/install_helpers.cmake)

# ====================================================== Common configuration ====================================================== #

add_compile_options(-fdiagnostics-color=always)

# ============================================================= Sources ============================================================ #

# Source directory
add_subdirectory(src)

# Tests directory
if(MASTER_PROJECT AND WITH_TESTS)

    # Add tests
    add_subdirectory(tests)
    # Add test
    add_test(NAME tests COMMAND cpp-utils-tests)

endif()

# ============================================================= Package ============================================================ #

# Package
if(${MASTER_PROJECT})

    # Generate package version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cpp-utils-${PROJECT_VERSION}/CppUtilsConfigVersion.cmake"
        COMPATIBILITY AnyNewerVersion
    )

    # Generate package config file
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cpp-utils-${PROJECT_VERSION}/CppUtilsConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpp-utils-${PROJECT_VERSION}
    )

    # Install config files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cpp-utils-${PROJECT_VERSION}/CppUtilsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cpp-utils-${PROJECT_VERSION}/CppUtilsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpp-utils-${PROJECT_VERSION}
    )

endif()
