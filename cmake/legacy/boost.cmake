# ====================================================================================================================================
# @file     boost.cmake
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 12:22:53 am
# @modified   Sunday, 26th June 2022 2:09:17 pm
# @project  cpp-utils
# @brief
#    
#    Helper CMake utility adding boost-headers interface library target to the project
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# -----------------------------------------------------------------------
# @brief Adds 'boost-headers' interface library target to the project
#    assuming that the boost git repository resides in the 
#    ${CMAKE_SOURCE_DIR}/extern/boost
# -----------------------------------------------------------------------
function(add_boost_headers)

    # Add library
    add_library(boost-headers INTERFACE)
    # Add boost includes
    target_include_directories(boost-headers 
        INTERFACE 
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/boost-headers/include>
    )
    # Disable RTTI mechanisms
    target_compile_options(boost-headers INTERFACE
        "-DBOOST_NO_RTTI"
        "-DBOOST_NO_TYPEID"
    )
    
    # Export library
    install(TARGETS boost-headers EXPORT boostHeaders)
    # Install headers
    install(
        DIRECTORY
            ${CMAKE_SOURCE_DIR}/src/boost-headers/include/boost/
        DESTINATION
            include/boost
    )

    # Install export
    install(EXPORT boostHeaders
        FILE
            boostHeadersTargets.cmake
        NAMESPACE
            cpp-utils::
        DESTINATION
            lib/cmake/cpp-utils-${PROJECT_VERSION}
    )

    # Set related variables
    set(Boost_FOUND        True)
    set(Boost_INCLUDE_DIRS ${CMAKE_PREFIX_PATH}/include)
    set(Boost_LIBRARIES    cpp-utils::boost-headers)
    
endfunction()
