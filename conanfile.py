# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Tuesday, 28th February 2023 1:37:22 pm
# @project    cpp-utils
# @brief      Conan package file for the cpp-utils library
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Any
   :synopsis: Conan package file for the cpp-utils library

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import re
import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import load, copy

# ========================================================== Requirements ========================================================== #

required_conan_version = ">=1.50.0"

# ============================================================ Script ============================================================== #

class HelloConan(ConanFile):
    
    name        = "cpp-utils"
    license     = "MIT"
    author      = "Krzysztof Pierczyk"
    description = "Set of abstract C++ utilities that can be used in all types of projects."
    topics      = ("estl", "estd")
    homepage    = "https://github.com/kpierczy/cpp-utils"

    # ---------------------------------------------------------------------------- #

    minimal_cpp_std = "20"

    # ---------------------------------------------------------------------------- #
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # ---------------------------------------------------------------------------- #

    exports = [ "license" ]

    exports_sources = [
        "cmake/*",
        "src/*",
        "tests/*",
        "CMakeLists.txt",
    ]

    # ---------------------------------------------------------------------------- #

    @property
    def _build_all(self):
        return bool(self.conf.get("user.build:all", default=True))
        
    # ---------------------------------------------------------------------------- #

    def requirements(self):
        self.requires("sml/1.1.6")
        self.requires("boost-ext-ut/1.1.9")
        self.requires("mp-units/0.7.0@mpusz/stable")


    def validate(self):
        
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self.minimal_cpp_std)


    def set_version(self):
        content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        version = re.search(r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)", content).group(1)
        self.version = version.strip()


    def layout(self):
        cmake_layout(self)


    def generate(self):

        toolchain = CMakeToolchain(self)

        # Parse conan options into the CMake build
        toolchain.variables["WITH_TESTS"] = self._build_all
        # Configure CMake
        toolchain.generate()
        
        # Generate dependencies for the CMake scripts
        toolchain_deps = CMakeDeps(self)
        toolchain_deps.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self._build_all:
            cmake.test()


    def package(self):

        # Install license
        copy(self, "license", self.source_folder, os.path.join(self.package_folder, "licenses"))
        # Install binaaries according to the CMake
        cmake = CMake(self)
        cmake.install()


    def package_info(self):

        # Extended std
        self.cpp_info.components[ "estd" ]
        # Extended STL
        self.cpp_info.components[ "estl" ]
        self.cpp_info.components[ "estl" ]
        # Extensions
        self.cpp_info.components[ "boost-sml-ext" ].requires.append('sml::sml')
        self.cpp_info.components[ "boost-sml-ext" ].requires.append('estd')
        self.cpp_info.components[ "mp-units-ext" ].requires.append('mp-units::mp-units')
        self.cpp_info.components[ "mp-units-ext" ].requires.append('estd')


# ================================================================================================================================== #
