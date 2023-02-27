# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Tuesday, 28th February 2023 12:05:02 am
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

from conan import ConanFile
from conan.tools.scm import Git
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
    homepage    = "https://github.com/rukkal/static-stl"
    revision    = "fb7a46c"

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

    def layout(self):
        cmake_layout(self)

    
    def source(self):

        # Download and checkout SSTL library
        git = Git(self, folder='sstl')
        git.clone(self.homepage, target='.')
        git.checkout(self.revision)
        # Patch sources
        apply_conandata_patches(self)


    def generate(self):

        toolchain = CMakeToolchain(self)

        # Helper routines
        def add_cmake_option(option_name, cmake_var_name):
            if getattr(self.options, option_name) is not None:
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
