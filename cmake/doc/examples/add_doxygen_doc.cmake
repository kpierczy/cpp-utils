# ====================================================================================================================================
# @file       add_doxygen_doc.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 12th May 2022 11:27:46 pm
# @modified   Sunday, 26th June 2022 3:52:22 pm
# @project    cpp-utils
# @brief      Usage examle of the add_doxygen_doc() function
#    
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Adding documentation target
add_doxygen_doc(doxygen_doc

    # Working directory
    WORKING_DIR ${PROJECT_SOURCE_DIR}
    # Output directory
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen
    # Tag file
    TAG_FILE ${PROJECT_NAME}.tag
    # Install dircetory
    INSTALL_DIR "doc/doxygen"
    # Doxyfiles
    DOXY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile

)
