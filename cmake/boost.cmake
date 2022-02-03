# ====================================================================================================================================
# @file     boost.cmake
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 12:22:53 am
# @modified Thursday, 3rd February 2022 9:36:57 pm
# @project  mbed-utils
# @brief
#    
#    Helper CMake utility adding boost-headers interface library target to the project
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# -----------------------------------------------------------------------
# @brief Adds 'boost-headers' interface library target to the project
#    assuming that the boost git repository resides in the 
#    ${CPP_UTILS_HOME}/extern/boost
# -----------------------------------------------------------------------
function(add_boost_headers)

    # Add library
    add_library(boost-headers INTERFACE)
    # Add boost includes
    target_include_directories(boost-headers 
        INTERFACE 
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CPP_UTILS_HOME}/extern/boost>
    )
    # Disable RTTI mechanisms
    target_compile_options(boost-headers INTERFACE
        "-DBOOST_NO_RTTI"
        "-DBOOST_NO_TYPEID"
    )
    
endfunction()
