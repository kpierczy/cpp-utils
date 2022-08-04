# ====================================================================================================================================
# @file       add_doxygen_doc.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 12th May 2022 11:27:46 pm
# @modified   Thursday, 4th August 2022 7:35:45 pm
# @project    cpp-utils
# @brief      Usage examle of the add_doxygen_doc() function
#    
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ========================================================== Dependencies ========================================================== #

# Define auxiliary commands
include(${PROJECT_SOURCE_DIR}/cmake/doc/add_sphinx_doc.cmake)
# Find sphinx
find_package(Doxygen)
find_package(Sphinx)

# ============================================================= Sources ============================================================ #

# List Doxygen source files
file(GLOB_RECURSE DOXYGEN_SOURCE_INCLUDE_FILES LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE DOXYGEN_SOURCE_SRC_FILES     LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Compile both lists
set(DOXYGEN_SOURCE_FILES ${DOXYGEN_SOURCE_INCLUDE_FILES} ${DOXYGEN_SOURCE_SRC_FILES})

# ============================================================== Docs ============================================================== #

# Adding documentation target
add_doxygen_doc(doxygen_doc

    # Working directory
    WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Output directory
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen
    # Source files
    SOURCE_FILES ${DOXYGEN_SOURCE_FILES}
    # Tag file
    TAG_FILE ${PROJECT_NAME}.tag
    # Install dircetory
    INSTALL_DIR "doc/doxygen"
    # Doxyfiles
    DOXY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile

)
