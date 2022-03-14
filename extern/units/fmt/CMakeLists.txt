# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Monday, 14th March 2022 9:29:20 pm
# @project  Winder
# @brief
#    
#    Lists file for the fork of the fmt library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ============================================================= Target ============================================================= #

# Add library
add_library(fmt INTERFACE)

# ========================================================== Configuration ========================================================= #

# Set headers-only build of the library
target_compile_definitions(fmt
    INTERFACE
        FMT_HEADER_ONLY=1
)

# #============================================================ Sources ============================================================ #

# Add project code
target_include_directories(fmt
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# ========================================================== Installation ========================================================== #

# Set path for CMake configuration files 
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/fmt-${PROJECT_VERSION})

# Export the targets to a script
install(EXPORT fmt-targets
    FILE
        fmtTargets.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install boost-sml target
install(TARGETS fmt
    EXPORT fmt-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set exported name of the `fmt` target to `fmt`
set_target_properties(fmt PROPERTIES EXPORT_NAME fmt)

# Install header files
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

