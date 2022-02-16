# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Wednesday, 16th February 2022 12:06:50 am
# @project  Winder
# @brief
#    
#    CMakeList for tests
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Source files
add_executable(cpp-utils-tests src/main.cpp)

# Include directories
target_include_directories(cpp-utils-tests
    PRIVATE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link libraries
target_link_libraries(cpp-utils-tests
    PRIVATE
        ${PROJECT_NAME}
        boost-ut
)
