# ====================================================================================================================================
# @file       add_sphinx_doc.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 12th May 2022 11:27:46 pm
# @modified   Sunday, 26th June 2022 3:52:26 pm
# @project    cpp-utils
# @brief      Usage examle of the add_sphinx_doc() function
#    
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Add documentation target (Sphinx)
add_sphinx_doc(sphinx_doc

    # Working directory (Sphinx)
    WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Source directory (Sphinx)
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    # Source files (Sphinx)
    SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    # Output directory (Sphinx)
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc/sphinx
    # Builders (Sphinx)
    BUILDERS "html"
    # Install dircetory (Sphinx)
    INSTALL_DIR "doc/sphinx"

    # Generate C++ API doc using Doxygen & Breathe tools
    GENERATE_CPP_API_DOC

    # Working directory (Doxygen)
    DOXYGEN_WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Output directory (Doxygen)
    DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc/sphinx/doxygen
    # Install dircetory (Doxygen)
    DOXYGEN_INSTALL_DIR "doc/sphinx-doxygen"
    # Doxygen config files (Doxygen)
    DOXYGEN_DOXY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    # Doxygen config overwrites (Doxygen)
    DOXYGEN_DOXY_LINES

        # Don't generate HTML & LaTeX output in the Sphinx run
        "GENERATE_HTML  = NO"
        "GENERATE_LATEX = NO"
    
)
