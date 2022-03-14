# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Monday, 14th March 2022 9:29:28 pm
# @project  Winder
# @brief
#    
#    Lists file for the fork of the gsl-lite library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ============================================================= Target ============================================================= #

# Add library
add_library(gsl-lite INTERFACE)

# #============================================================ Sources ============================================================ #

# Add project code
target_include_directories(gsl-lite
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# ========================================================== Installation ========================================================== #

# Set path for CMake configuration files 
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/gsl-lite-${PROJECT_VERSION})

# Export the targets to a script
install(EXPORT gsl-lite-targets
    FILE
        gslLiteTargets.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install boost-sml target
install(TARGETS gsl-lite
    EXPORT gsl-lite-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set exported name of the `gsl-lite` target to `gsl-lite`
set_target_properties(gsl-lite PROPERTIES EXPORT_NAME gsl-lite)

# Install header files
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

