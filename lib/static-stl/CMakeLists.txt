# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 5th January 2022 12:23:05 pm
# @modified   Wednesday, 1st March 2023 7:23:39 pm
# @project    cpp-utils
# @brief      Cmake package for the static-stl library
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
project(static-stl VERSION 1.0 LANGUAGES CXX)

# ============================================================= Target ============================================================= #

# Add library
add_library(static-stl INTERFACE)

# Add include directories
target_include_directories(static-stl INTERFACE include)
# Set compile options
target_compile_options(static-stl INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-Wall>" )
# Add preprocessor definitions
if(SSTL_ASSERT)
    target_compile_definitions(static-stl INTERFACE SSTL_ASSERT=${SSTL_ASSERT})
endif()
if(SSTL_ASSERT_HEADER)
    target_compile_definitions(static-stl INTERFACE SSTL_ASSERT_HEADER=${SSTL_ASSERT_HEADER})
endif()
# Link to assert-providing library if given
if(SSTL_ASSERT_LIB)
    target_link_libraries(static-stl INTERFACE ${SSTL_ASSERT_LIB})
endif()

# ============================================================ Installs ============================================================ #

# Install header files
install(
    DIRECTORY
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/sstl/include/
    TYPE
        INCLUDE
)

# Install targets
install(TARGETS static-stl)

# ====================================================== Helper configuration ====================================================== #

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()

# ================================================================================================================================== #
