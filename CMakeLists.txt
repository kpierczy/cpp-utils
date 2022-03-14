# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Thursday, 3rd February 2022 10:11:45 am
# @modified Monday, 14th March 2022 9:49:08 pm
# @project  cpp-utils
# @brief
#    
#    Top-level CMake file of the project
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

# Set root of the project
set(CPP_UTILS_HOME ${CMAKE_CURRENT_LIST_DIR})
if(NOT ${MASTER_PROJECT})
    set(CPP_UTILS_HOME ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
endif()

# Project's header
project(cpp-utils VERSION 1.0 LANGUAGES CXX)

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
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.cmake)

# Add boost::ext::* libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/boost-ext)
# Add mp-units library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/units)

# Add private targets
if(${MASTER_PROJECT})
    message("This is ${CPP_UTILS_HOME}!!!")
    # Add boost headers
    add_boost_headers()

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
