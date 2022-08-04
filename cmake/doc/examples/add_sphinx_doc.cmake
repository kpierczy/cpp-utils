# ====================================================================================================================================
# @file       add_sphinx_doc.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 12th May 2022 11:27:46 pm
# @modified   Thursday, 4th August 2022 7:37:08 pm
# @project    cpp-utils
# @brief      Usage examle of the add_sphinx_doc() function
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

# Add documentation target (Sphinx)
add_sphinx_doc(sphinx_doc

    # Working directory (Sphinx)
    WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Source directory (Sphinx)
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    # Source files (Sphinx)
    SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    # Output directory (Sphinx)
    OUTPUT_DIR ${PROJECT_SOURCE_DIR}/doc/sphinx
    # Builders (Sphinx)
    BUILDERS "html"
    # Install dircetory (Sphinx)
    INSTALL_DIR "${PROJECT_SOURCE_DIR}/doc/sphinx"

    # Generate C++ API doc using Doxygen & Breathe tools
    GENERATE_CPP_API_DOC

    # Working directory (Doxygen)
    DOXYGEN_WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Output directory (Doxygen)
    DOXYGEN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/doc/sphinx/doxygen
    # Install dircetory (Doxygen)
    DOXYGEN_INSTALL_DIR "${PROJECT_SOURCE_DIR}/doc/sphinx-doxygen"
    # Doxygen config files (Doxygen)
    DOXYGEN_DOXY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    # Doxygen source files
    DOXYGEN_SOURCE_FILES ${DOXYGEN_SOURCE_FILES}
    # Doxygen config overwrites (Doxygen)
    DOXYGEN_DOXY_LINES

        # Don't generate HTML & LaTeX output in the Sphinx run
        "GENERATE_HTML  = NO"
        "GENERATE_LATEX = NO"
    
)
