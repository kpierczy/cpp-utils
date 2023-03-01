# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 1st March 2023 2:27:25 am
# @project    cpp-utils
# @brief      CMakeList for project extended-std' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================= Options ============================================================ #

option(WITH_BOOST_SML_EXTENSIONS "If True lib-extensions-boost-sml will be built" ON) 
option(WITH_MP_UNITS_EXTENSIONS  "If True lib-extensions-mp-units  will be built" ON)

# ============================================================= Targets ============================================================ #

# Source files
add_library(lib-extensions INTERFACE)

# Subdirectories
if(WITH_BOOST_SML_EXTENSIONS)
    add_subdirectory(boost-sml)
endif()
if(WITH_MP_UNITS_EXTENSIONS)
    add_subdirectory(mp-units)
endif()

# Sublibraries
if(WITH_BOOST_SML_EXTENSIONS)
    target_link_libraries(lib-extensions INTERFACE lib-extensions-boost-sml)
endif()
if(WITH_MP_UNITS_EXTENSIONS)
    target_link_libraries(lib-extensions INTERFACE lib-extensions-mp-units)
endif()

# Export library and install export set
export_and_install(EXPORT lib-extensions-export TARGETS lib-extensions )

