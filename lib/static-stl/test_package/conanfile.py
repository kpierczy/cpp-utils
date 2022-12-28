# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 10:20:00 pm
# @modified   Wednesday, 28th December 2022 11:14:04 pm
# @project    embedded-utils
# @brief      Test package for the static-stl package
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: OS Independent
   :synopsis: Test package for the static-stl package

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.build import cross_building

# ============================================================ Script ============================================================== #

class HelloTestConan(ConanFile):

    settings   = "os", "compiler", "build_type", "arch"
    generators = 'CMakeDeps', 'CMakeToolchain', 'VirtualBuildEnv', 'VirtualRunEnv'
    apply_env  = False
    test_type  = 'explicit'

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        cmake_layout(self)
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not cross_building(self):
            cmd = os.path.join(self.cpp.build.bindirs[0], "test")
            self.run(cmd, env="conanrun")

# ================================================================================================================================== #