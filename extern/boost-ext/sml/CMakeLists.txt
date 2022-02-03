# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Jusiak (krzysztof@jusiak.net)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified Thursday, 3rd February 2022 7:17:10 pm
# @project    Winder
# @brief
#    
#    CMake package for Boost.SML library
#    
# @copyright Krzysztof Pierczyk © 2021
# @see https://github.com/boost-ext/boost-sml
# ====================================================================================================================================

# Establish build type
set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
endif()

# ====================================================================================================================================
# --------------------------------------------------------- Standalone build ---------------------------------------------------------
# ====================================================================================================================================

# ================================================================================================================================== #

cmake_minimum_required(VERSION 3.10)
project(boost-sml VERSION 1.1.4 LANGUAGES CXX)

# ============================================================ Includes ============================================================ #

# Include CTests
include(CTest)
# Include helper modules
include(CheckCXXCompilerFlag)
# Include standard isntall paths
include(GNUInstallDirs)
# Import helper functions for `ConfigVersion.cmak` file
include(CMakePackageConfigHelpers)

# ============================================================= Options ============================================================ #

# Build options
option(SML_BUILD_BENCHMARKS "Build benchmarks"          OFF)
option(SML_BUILD_EXAMPLES   "Build examples"            OFF)
option(SML_BUILD_TESTS      "Build tests"               OFF)
option(SML_USE_EXCEPTIONS   "Do not disable exceptions" ON)

# ========================================================== System check ========================================================== #

# Requirements check
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 6.0.0)
    message(FATAL_ERROR "boost-sml requires GCC >= 6.0.0")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 3.5.0)
    message(FATAL_ERROR "boost-sml requires Clang >= 3.5.0")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
    message(FATAL_ERROR "boost-sml requires Visual Studio 14 2015 at least")
endif()

# Standards check
check_cxx_compiler_flag(-std=c++14 HAS_CXX14_FLAG)
check_cxx_compiler_flag(-std=c++17 HAS_CXX17_FLAG)
check_cxx_compiler_flag(-std=c++2a HAS_CXX20_FLAG)
# Standard choice
if(HAS_CXX20_FLAG)
    set(CMAKE_CXX_STANDARD 20)
elseif(HAS_CXX17_FLAG)
    set(CMAKE_CXX_STANDARD 17)
elseif(HAS_CXX14_FLAG)
    set(CMAKE_CXX_STANDARD 14)
else()
    message(FATAL_ERROR "boost-sml requires c++14")
endif()
# Check if proper standard has been selected
if(NOT (DEFINED CMAKE_CXX_STANDARD) OR CMAKE_CXX_STANDARD STREQUAL "" OR CMAKE_CXX_STANDARD LESS 14)
    message(FATAL_ERROR "boost-sml requires c++14")
endif()

# Check if GCC-like compiler given
set(IS_COMPILER_GCC_LIKE FALSE)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
"${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR
"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(IS_COMPILER_GCC_LIKE TRUE)
endif()

# ========================================================== Configuration ========================================================= #

# Set standard requirements
set(CXX_STANDARD_REQUIRED ON)

# Organize targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Configure installation
install(DIRECTORY "include/boost" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# ============================================================= Target ============================================================= #

# Add library
add_library(boost-sml INTERFACE)
# Alias librarie's name
add_library(Boost::sml ALIAS boost-sml)

#Add include directories
target_include_directories(boost-sml INTERFACE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# MSVC build
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    
    # Compile options
    target_compile_definitions(boost-sml
        # Avoid Win macro definition of min/max, use std one
        INTERFACE NOMINMAX 
        # Disable security-paranoia warning
        INTERFACE _SCL_SECURE_NO_WARNINGS 
        INTERFACE _CRT_SECURE_NO_WARNINGS
    )
    # C++17 compile options
    if(CMAKE_CXX_STANDARD GREATER_EQUAL 17)
        target_compile_definitions(boost-sml INTERFACE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    endif()

# GCC/Clang build
elseif (IS_COMPILER_GCC_LIKE)

    # Compile options (@see https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
    target_compile_options(boost-sml
        # Stops on first error (@modified: don't require)
        # INTERFACE "-Wfatal-errors"
        # Enables all the warnings about constructions
        INTERFACE "-Wall"
        # Print extra warning messages
        INTERFACE "-Wextra"
        # Make all warnings into errors (@modified: don't require)
        # INTERFACE "-Werror"
        # Issue all the warnings demanded by strict ISO C and ISO C++ (@modified: don't require)
        # INTERFACE "-pedantic"
        # Like -pedantic, except that errors are produced rather than warnings (@modified: don't require)
        # INTERFACE "-pedantic-errors"
        # Silence ABI-related notes (@modified @added)
        INTERFACE "-Wno-psabi"
    )

    # GCC-specific options (@see http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(boost-sml
            INTERFACE "-ftrack-macro-expansion=0"
            INTERFACE "-fno-diagnostics-show-caret"
        )
    endif()

    # No-exception build
    if (NOT ${SML_USE_EXCEPTIONS})
        target_compile_options(boost-sml INTERFACE "-fno-exceptions")
    endif()

endif ()

# ======================================================= Target installation ====================================================== #

if(${MASTER_PROJECT})

    # Set path for CMake configuration files 
    set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/boost-sml-${PROJECT_VERSION})

    # Create a ConfigVersion.cmake file
    write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/smlConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Generate `smlConfig.cmake` file
    configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/smlConfig.cmake.in
        ${CMAKE_BINARY_DIR}/smlConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

    # Export the targets to a script
    install(EXPORT boost-sml-targets
        FILE
            smlTargets.cmake
        NAMESPACE
            Boost::
        DESTINATION
            ${INSTALL_CONFIGDIR}
    )

    #Install the config and configversion files
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/smlConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/smlConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
    )

    # Install boost-sml target
    install(TARGETS boost-sml
        EXPORT boost-sml-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    # Set exported name of the `boost-sml` target to `boost-sml`
    set_target_properties(boost-sml PROPERTIES EXPORT_NAME boost-sml)

    # Install header files
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif()

# ========================================================= Targets exports ======================================================== #

if(${MASTER_PROJECT})

    # Export targets
    export(EXPORT boost-sml-targets
        FILE 
            ${CMAKE_CURRENT_BINARY_DIR}/boost-sml.cmake
        NAMESPACE 
            Boost::
    )

    # Register package in the User Package Registry
    export(PACKAGE boost-sml)

endif()

# ======================================================= Additional targets ======================================================= #

# Set common include directories for additional targets
include_directories($<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Helper target addre
function(add_example exe_name bm_name src_name)
    add_executable(${exe_name} ${src_name})
    target_link_libraries(${exe_name} PUBLIC boost-sml)
    add_test(${bm_name} ${exe_name})
endfunction()

# Compile benchmarks
if (SML_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()

# Compile examples
if (SML_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

# Compile tests
if (SML_BUILD_TESTS)
    add_subdirectory(test)
endif()

# ====================================================== Helper configuration ====================================================== #

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()

# ================================================================================================================================== #
