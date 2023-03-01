# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 7th July 2021 7:57:46 pm
# @modified   Wednesday, 1st March 2023 2:26:38 am
# @project    cpp-utils
# @brief      CMakeList for project extended-std' library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================= Options ============================================================ #

option(WITH_ESTD_PREPROCESSOR "If True estd-preprocesor will be built" ON) 

# ============================================================= Target ============================================================= #

# Source files
add_library(estd INTERFACE)

# Subdirectories
add_subdirectory(bits)
add_subdirectory(concepts)
add_subdirectory(enum)
add_subdirectory(miscellaneous)
add_subdirectory(pointers)
add_subdirectory(result)
add_subdirectory(string)
add_subdirectory(synchronisation)
add_subdirectory(traits)
if(WITH_ESTD_PREPROCESSOR)
    add_subdirectory(preprocessor)
endif()

# Sublibraries
target_link_libraries(estd 
    INTERFACE 
        estd-bits
        estd-concepts
        estd-enum
        estd-miscellaneous
        estd-pointers
        estd-result
        estd-string
        estd-synchronisation
        estd-traits)
if(WITH_ESTD_PREPROCESSOR)
    target_link_libraries(estd INTERFACE estd-preprocessor)
endif()

# Require C++20 standard
target_compile_features(estd INTERFACE cxx_std_20)

# Export library and install export set
export_and_install(EXPORT estd-export TARGETS estd )

