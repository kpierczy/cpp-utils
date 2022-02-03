# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Wednesday, 1st December 2021 10:54:49 am
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
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
