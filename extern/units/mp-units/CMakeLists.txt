# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Monday, 14th March 2022 9:34:43 pm
# @project  Winder
# @brief
#    
#    Lists file for the fork of the mp-units library
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ============================================================= Target ============================================================= #

# Add library
add_library(mp-units INTERFACE)

# Add CMake module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ========================================================== Configruation ========================================================= #

# Set restrictive compilation warnings
include(warnings)
set_warnings()

# Configure library with compile-time definitions
target_compile_definitions(mp-units
    INTERFACE
        # Set all contracts checking in a Debug build
        $<$<CONFIG:Debug>:gsl_CONFIG_CONTRACT_CHECKING_AUDIT>
        # Disable some parts of the library to speed up compilation times
        # -DUNITS_NO_ALIASES
        # -DUNITS_NO_REFERENCES
        # -DUNITS_NO_LITERALS
)

# #============================================================ Sources ============================================================ #

# Add project code
target_include_directories(mp-units
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-typographic/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-imperial/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-hep/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-fps/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq-natural/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq-iec80000/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-international/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-iau/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-cgs/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-uscs/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/core-io/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/core-fmt/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/core/include>
)

# Add dependencies
target_link_libraries(mp-units
    INTERFACE
        fmt
        gsl-lite
)

# Export target
target_link_libraries(mp-units
    INTERFACE
        fmt
        gsl-lite
)

# ========================================================== Installation ========================================================== #

# Set path for CMake configuration files 
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mp-units-${PROJECT_VERSION})

# Export the targets to a script
install(EXPORT mp-units-targets
    FILE
        mpUnitsTargets.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install boost-sml target
install(TARGETS mp-units
    EXPORT mp-units-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set exported name of the `mp-units` target to `mp-units`
set_target_properties(mp-units PROPERTIES EXPORT_NAME mp-units)

# Install header files
install(
    DIRECTORY 
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-typographic/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-imperial/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-hep/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-fps/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/isq-natural/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/isq-iec80000/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-international/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-iau/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-cgs/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/si-uscs/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/systems/isq/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/core-io/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/core-fmt/include/
        ${CMAKE_CURRENT_LIST_DIR}/src/core/include/
    DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}
)
