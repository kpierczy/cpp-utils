# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Jusiak (krzysztof@jusiak.net)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Sunday, 26th June 2022 3:48:46 pm
# @project    Winder
# @brief
#    
#    CMake package for Boost.UT library
#    
# @copyright Krzysztof Pierczyk © 2021
# @see https://github.com/boost-ext/boost-ut
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

cmake_minimum_required(VERSION 3.12...3.20)
project(boost-ut VERSION 1.1.8 LANGUAGES CXX)

# ============================================================= Options ============================================================ #

# Standard-dependent options
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # Default C++ standard
    set(CMAKE_CXX_STANDARD 20 CACHE STRING "Default value for CXX_STANDARD property of targets.")
    # Options
    option(CMAKE_CXX_STANDARD_REQUIRED "Default value for CXX_STANDARD_REQUIRED property of targets." YES)
    option(CMAKE_CXX_EXTENSIONS        "Default value for CXX_EXTENSIONS property of targets."         NO)
endif()

# Other options
option(BOOST_UT_ENABLE_MEMCHECK   "Run the unit tests and examples under valgrind if it is found" OFF)
option(BOOST_UT_ENABLE_COVERAGE   "Run coverage"                                                  OFF)
option(BOOST_UT_ENABLE_SANITIZERS "Run static analysis"                                           OFF)
option(BOOST_UT_BUILD_BENCHMARKS  "Build the benchmarks"                                          OFF)
option(BOOST_UT_BUILD_EXAMPLES    "Build the examples"                                            OFF)
option(BOOST_UT_BUILD_TESTS       "Build the tests"                                               OFF)
option(BOOST_UT_DISABLE_MODULE    "Disable boost-ut module"                                             OFF)

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

# ========================================================== Configuration ========================================================= #

# Enable converage feature
if(BOOST_UT_ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

# Enable sanitizer feature
if(BOOST_UT_ENABLE_SANITIZERS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined")
endif()

# Enable C++20 modules feature
if(BOOST_UT_DISABLE_MODULE)
    target_compile_definitions(boost-ut INTERFACE BOOST_UT_DISABLE_MODULE)
endif()

# ============================================================= Target ============================================================= #

# Add library
add_library(boost-ut INTERFACE)
# Alias librarie's name
add_library(ut        ALIAS boost-ut)
add_library(Boost::ut ALIAS boost-ut)

# Set installation include dirs
set(INCLUDE_INSTALL_DIR include/boost/boost-ut/include)

# Add include directories
target_include_directories(boost-ut 
    INTERFACE 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)

# Add compile features
if(APPLE)
  target_compile_features(boost-ut INTERFACE cxx_std_20)
else()
  target_compile_features(boost-ut INTERFACE cxx_std_17)
endif()

# Add compile options (Clang)
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")

    # Clang-cl
    if(WIN32)

        # FIXME: we should not export this pedantic options! CK
        target_compile_options(boost-ut
            INTERFACE
                -Wall
                -Wextra
                # FIXME -Werror
                -Wno-c++98-c++11-c++14-c++17-compat-pedantic
                -Wno-c++98-c++11-compat
                -Wno-c++98-compat
                -Wno-c++98-compat-pedantic
                -Wno-c99-extensions
                -Wno-pedantic
        )

    # Clang
    else()
        add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    endif()
  
# Add compile options (GCC)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  
    # FIXME: we should not export this pedantic options! CK
    target_compile_options(boost-ut
        INTERFACE
            "$<$<COMPILE_LANGUAGE:CXX>:-Wall>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wextra>"
            # TODO: why not simpply -Wpedantic
            # Cast warnings to errors (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Werror>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wcast-align>"
            # Require strict align when casting (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wcast-align=strict>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wcast-qual>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wdouble-promotion>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wduplicated-branches>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wduplicated-cond>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wlogical-op>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wmissing-declarations>"
            # Require explicit includes (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wmissing-include-dirs>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wnull-dereference>"
            # Require no old-style casts (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wpointer-arith>"
            # Require no redundant declarations (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wredundant-decls>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wsign-conversion>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wswitch-enum>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wtrampolines>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wunused-but-set-variable>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wunused-result>"
            # Require pedantic casting (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wuseless-cast>"
            # Require not to treat nullptr as 0 (@modified don't require)
            # "$<$<COMPILE_LANGUAGE:CXX>:-Wzero-as-null-pointer-constant>"
            # @fixme
            "$<$<COMPILE_LANGUAGE:CXX>:-Wno-undef>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-declarations>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wno-sign-conversion>"
            "$<$<COMPILE_LANGUAGE:CXX>:-Wno-float-equal>"
  )
  
# Add compile options (Windows)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
endif()

# ======================================================= Target installation ====================================================== #

if(${MASTER_PROJECT})

    # Create target Boost::boost-ut and install target
    packageProject( 
        NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        NAMESPACE Boost
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
        INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
        COMPATIBILITY SameMajorVersion
    )

endif()

# ======================================================= Additional targets ======================================================= #

if(${MASTER_PROJECT})

    # Add custom target for printing style info
    add_custom_target(style)
    add_custom_command( TARGET style 
        COMMAND find 
            ${CMAKE_CURRENT_LIST_DIR}/benchmark
            ${CMAKE_CURRENT_LIST_DIR}/example
            ${CMAKE_CURRENT_LIST_DIR}/include
            ${CMAKE_CURRENT_LIST_DIR}/test 
        -iname "*.hpp" -or -iname "*.cpp" | xargs clang-format -i
    )

    # Note: now we can use the target Boost::boost-ut
    include(cmake/AddCustomCommandOrTest.cmake)

    # Compile benchmarks
    if(BOOST_UT_BUILD_BENCHMARKS)
        add_subdirectory(benchmark)
    endif()

    # Compile examples
    if(BOOST_UT_BUILD_EXAMPLES)
        add_subdirectory(example)
    endif()

    # Compile tests
    if(BOOST_UT_BUILD_TESTS)
        enable_testing()
        add_subdirectory(test)
    endif()

endif()

# ====================================================== Helper configuration ====================================================== #

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()

# ================================================================================================================================== #
