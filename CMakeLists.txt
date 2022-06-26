# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 3rd February 2022 10:11:45 am
# @modified   Sunday, 26th June 2022 3:02:16 pm
# @project    cpp-utils
# @brief      Top-level CMake file of the project
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.16)

# ====================================================== Project configuration ===================================================== #

# Establish build type
set(MASTER_PROJECT OFF)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  set(MASTER_PROJECT ON)
endif()

# Project's header
project(cpp-utils VERSION 1.0 LANGUAGES CXX)

# ============================================================= Options ============================================================ #

option(WITH_CUSTOM_BOOST     "If ON includes boost header sources installed by the project's setup into the source tree" $ENV{CPP_UTILS_INSTALL_BOOST_HEADERS})
option(WITH_CUSTOM_BOOST_EXT "If ON includes boost extensions sources by Kris Jusiak into the source tree"               ON                                   )
option(WITH_CUSTOM_MP_UNITS  "If ON includes mp-units sources by Matusz Pusz into the source tree"                       ON                                   )

# ============================================================ Includes ============================================================ #

include(CTest)
include(CMakePackageConfigHelpers)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/install_helpers.cmake)

# ===================================================== Toolchain configuration ==================================================== #

if(${MASTER_PROJECT})

    # Set C++ standard for project's targets
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_CXX_EXTENSIONS True)

endif()

# ========================================================== Dependencies ========================================================== #

# Include helper scripts
if(WITH_CUSTOM_BOOST)
    add_subdirectory(src/boost-headers)
else()
    find_package(Boost REQUIRED)
endif()

# Add boost::ext::* libraries
if(WITH_CUSTOM_BOOST_EXT)
    add_subdirectory(extern/boost-ext)
else()
    find_package(di  REQUIRED)
    find_package(sml REQUIRED)
    find_package(ut  REQUIRED)
endif()

# Add mp-units library
if(WITH_CUSTOM_MP_UNITS)
    add_subdirectory(extern/mp-units)
else()
    find_package(mp-units REQUIRED)
endif()

# ============================================================= Sources ============================================================ #

# Source directory
add_subdirectory(src)

# Tests directory
if(${MASTER_PROJECT})

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
