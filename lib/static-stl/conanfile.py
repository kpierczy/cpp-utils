# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Wednesday, 28th December 2022 11:48:37 pm
# @project    cpp-utils
# @brief      Conan package file for the static-stl library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Any
   :synopsis: Conan package file for the static-stl library

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

from conans import ConanFile
from conans.tools import Git
from conan.tools.files import apply_conandata_patches
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

# ============================================================ Script ============================================================== #

class HelloConan(ConanFile):
    
    name        = "static-stl"
    version     = "1.0"
    license     = "Unknown"
    author      = "Kean Mariotti"
    description = "The SSTL is a partial reimplementation of the C++ Standard Template Library (STL) that strictly avoids the" + \
                  "use of dynamic memory allocation."
    topics      = ("stl", "static")
    url         = "https://github.com/rukkal/static-stl"
    url_version = "fb7a46c"

    # ---------------------------------------------------------------------------- #
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    # Library options
    options = {
        'sstl_assert'        : [ None, 'ANY' ],
        'sstl_assert_header' : [ None, 'ANY' ],
        'sstl_assert_lib'    : [ None, 'ANY' ],
    }
    default_options = {
        'sstl_assert'        : None,
        'sstl_assert_header' : None,
        'sstl_assert_lib'    : None,
    }

    # ---------------------------------------------------------------------------- #

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "include/*", "sstl/include/*", "patches/*"

    # ---------------------------------------------------------------------------- #
    
    def source(self):

        # Download and checkout SSTL library
        git = Git(folder='sstl')
        git.clone(self.url)
        git.checkout(self.url_version)
        # Patch sources
        apply_conandata_patches(self)


    def layout(self):
        cmake_layout(self)


    def generate(self):

        toolchain = CMakeToolchain(self)

        # Helper routines
        def add_cmake_option(option_name, cmake_var_name):
            if hasattr(self.options, option_name):
                toolchain.variables[cmake_var_name] = getattr(self.options, option_name)

        # Add CMake options as needed
        add_cmake_option('sstl_assert',        'SSTL_ASSERT'       )
        add_cmake_option('sstl_assert_header', 'SSTL_ASSERT_HEADER')
        add_cmake_option('sstl_assert_lib',    'SSTL_ASSERT_LIB'   )
        
        # Generate CMake files
        toolchain.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()


    def package_info(self):
        self.cpp_info.components[ "static-stl" ]


# ================================================================================================================================== #