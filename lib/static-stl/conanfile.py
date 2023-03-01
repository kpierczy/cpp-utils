# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Wednesday, 1st March 2023 7:29:12 pm
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

class StaticStlConan(ConanFile):
    
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

    # ---------------------------------------------------------------------------- #

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = [
        "CMakeLists.txt",
        "include/*",
        "sstl/include/*",
        "patches/*",
    ]

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
        toolchain.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()


    def package_id(self):
        self.info.clear()


# ================================================================================================================================== #
