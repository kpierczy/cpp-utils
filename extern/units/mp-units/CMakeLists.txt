# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Thursday, 2nd December 2021 2:33:26 am
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-typographic/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-imperial/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-hep/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-fps/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq-natural/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq-iec80000/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-international/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-iau/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-cgs/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/si-uscs/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/isq/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core-io/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core-fmt/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/include
)

# Add dependencies
target_link_libraries(mp-units
    INTERFACE
        fmt
        gsl-lite
)
