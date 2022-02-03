# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   rukkal
# @date     Wednesday, 5th January 2022 12:23:05 pm
# @modified Wednesday, 5th January 2022 12:47:47 pm
# @project  Winder
# @brief
#    
#    Cmake package for the static-stl library
#    
# @source https://github.com/rukkal/static-stl
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

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(static-stl VERSION 1.0.0 LANGUAGES CXX)

# ========================================================== Dependencies ========================================================== #

# Install-setup dependency
if(CMAKE_VERSION VERSION_LESS 3.20.0)

    # @see https://github.com/TheLartians/PackageProject.cmake/pull/19
    include(cmake/PackageProject.cmake) 
    
else()

    # @see https://github.com/cpm-cmake/CPM.cmake
    include(cmake/CPM.cmake)

    # Download PackageProject.cmake (it will be used to make target installable)
    CPMAddPackage(
        NAME PackageProject.cmake
        GITHUB_REPOSITORY TheLartians/PackageProject.cmake
        VERSION 1.6.0
    )

endif()

# ============================================================= Target ============================================================= #

# Add library
add_library(sstl INTERFACE)

# Add include directories
target_include_directories(sstl 
    INTERFACE 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Set compile options
target_compile_options(sstl
    INTERFACE
        "$<$<COMPILE_LANGUAGE:CXX>:-Wall>"
)

# Link to Mbed libraries
target_link_libraries(sstl
    INTERFACE
        mbed-os
)

# ======================================================= Target installation ====================================================== #

if(${MASTER_PROJECT})

    # Create target sstl and install target
    packageProject( 
        NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
        INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
        COMPATIBILITY SameMajorVersion
    )

endif()

# ====================================================== Helper configuration ====================================================== #

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()

# ================================================================================================================================== #
