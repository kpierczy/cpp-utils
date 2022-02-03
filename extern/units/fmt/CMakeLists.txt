# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:25:07 am
# @modified Wednesday, 1st December 2021 11:53:08 am
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
