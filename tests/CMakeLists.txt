# ====================================================================================================================================
# @file     CMakeLists.txt
# @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date     Wednesday, 7th July 2021 7:57:46 pm
# @modified Thursday, 3rd February 2022 8:04:05 pm
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