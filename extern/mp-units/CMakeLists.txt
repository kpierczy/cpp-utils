# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 1st December 2021 10:21:39 am
# @modified Wednesday, 1st December 2021 10:21:55 am
# @project  Winder
# @brief
#    
#    CMake file for local fork of the mp-units library with dependencies
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Include fmt library
add_subdirectory(fmt)
# Include gsl-lite library
add_subdirectory(gsl-lite)
# Include mp-units library
add_subdirectory(mp-units)
