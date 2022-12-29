# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Thursday, 29th December 2022 12:58:23 am
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

from distutils.dir_util import copy_tree
from conans import ConanFile
from conans.tools import Git
from conan.tools.files import apply_conandata_patches
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

# ============================================================ Script ============================================================== #

class HelloConan(ConanFile):
    
    name        = "frozen"
    version     = "1.1.2-alpha"
    license     = "Apache-2.0"
    author      = "serge-sans-paille"
    description = "Header-only library that provides 0 cost initialization for immutable containers, fixed-size " + \
                  "containers, and various algorithms."
    topics      = ("stl", "constexpr")
    url         = "https://github.com/serge-sans-paille/frozen"
    url_version = "079f73c"

    # ---------------------------------------------------------------------------- #
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    # Library options
    options = {
        'with_exceptions' : [ False, True ],
        'with_tests'      : [ False, True ],
        'with_benchmark'  : [ False, True ],
        'with_coverage'   : [ False, True ],
    }
    default_options = {
        'with_exceptions' : True,
        'with_tests'      : False,
        'with_benchmark'  : False,
        'with_coverage'   : False,
    }

    # ---------------------------------------------------------------------------- #

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "cmake/*", "include/*", "tests/*", "patches/*"

    # ---------------------------------------------------------------------------- #
    
    def layout(self):
        cmake_layout(self)

        
    def source(self):

        # Download and checkout SSTL library
        git = Git(folder='frozen')
        git.clone(self.url)
        git.checkout(self.url_version)
        # Copy files to the source folder
        copy_tree('./frozen', '.')
        # Patch sources
        apply_conandata_patches(self)


    def generate(self):

        toolchain = CMakeToolchain(self)

        # Helper routines
        def add_cmake_option(option_name, cmake_var_name):
            option = getattr(self.options, option_name)
            if option == True:
                toolchain.variables[cmake_var_name] = 'ON'
            else:
                toolchain.variables[cmake_var_name] = 'OFF'

        # Add CMake options as needed
        add_cmake_option('with_exceptions', 'frozen.exceptions')
        add_cmake_option('with_tests',      'frozen.tests'     )
        add_cmake_option('with_benchmark',  'frozen.benchmark' )
        add_cmake_option('with_coverage',   'frozen.coverage'  )

        toolchain.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()


    def package_info(self):
        self.cpp_info.components[ "frozen" ]


# ================================================================================================================================== #
