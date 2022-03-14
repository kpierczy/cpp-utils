# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Jusiak (krzysztof@jusiak.net)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified Monday, 14th March 2022 9:26:06 pm
# @project    Winder
# @brief
#    
#    CMake package for Boost.DI library
#    
# @copyright Krzysztof Pierczyk © 2021
# @see https://github.com/boost-ext/di
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

cmake_minimum_required(VERSION 3.0)
project(di VERSION 1.0 LANGUAGES CXX)

# ============================================================ Includes ============================================================ #

# Include standard isntall paths
include(GNUInstallDirs)
# Import helper functions for `ConfigVersion.cmak` file
include(CMakePackageConfigHelpers)

# ============================================================= Options ============================================================ #

# Build options
option(DI_BUILD_EXAMPLES "Build examples" OFF)
option(DI_BUILD_TESTS    "Build tests"    OFF)

# ============================================================= Target ============================================================= #

# Add library
add_library(boost-di INTERFACE)
# Alias librarie's name
add_library(Boost::di ALIAS boost-di)

#Add include directories
target_include_directories(boost-di INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extension/include>
)

# Set GCC-specific options
if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
 
    # Provide compile options
    target_compile_options(boost-di INTERFACE
        "-fno-exceptions"
        "-Wall"
        "-Wextra"
        # Require pedantic (@modified don't require)
        # "-pedantic"
        # Require pedantic and turn warnings into errors (@modified don't require)
        # "-pedantic-errors"
        # Turn warnings into errors (@modified don't require)
        # "-Werror"
    )

else()
    message(WARNING "Unsupported compiler!")
endif()

# ======================================================= Target installation ====================================================== #

# Set path for CMake configuration files 
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/boost-di-${PROJECT_VERSION})

if(${MASTER_PROJECT})

    # Create a ConfigVersion.cmake file
    write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/diConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Generate `diConfig.cmake` file
    configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/diConfig.cmake.in
        ${CMAKE_BINARY_DIR}/diConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

    #Install the config and configversion files
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/diConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/diConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
    )

endif()

# Export the targets to a script
install(EXPORT boost-di-targets
    FILE
        diTargets.cmake
    NAMESPACE
        Boost::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install di target
install(TARGETS boost-di
    EXPORT boost-di-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set exported name of the `boost-di` target to `boost-di`
set_target_properties(boost-di PROPERTIES EXPORT_NAME boost-di)

# Install header files
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# ========================================================= Targets exports ======================================================== #

if(${MASTER_PROJECT})

    # Export targets
    export(EXPORT boost-di-targets
        FILE 
            ${CMAKE_CURRENT_BINARY_DIR}/boost-di.cmake
        NAMESPACE 
            Boost::
    )

    # Register package in the User Package Registry
    export(PACKAGE boost-di)

endif()

# ======================================================= Additional targets ======================================================= #

# Build tests
if (DI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(extension/test)
    add_subdirectory(test)
endif ()

# Build examples
if (DI_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()


# ====================================================== Helper configuration ====================================================== #

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()

# ================================================================================================================================== #
