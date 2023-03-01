# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 10:20:00 pm
# @modified   Wednesday, 1st March 2023 7:29:05 pm
# @project    cpp-utils
# @brief      Test package for the frozen package
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: OS Independent
   :synopsis: Test package for the frozen package

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run

# ============================================================ Script ============================================================== #

class FrozenTestConan(ConanFile):

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
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "test")
            self.run(cmd, env="conanrun")

# ================================================================================================================================== #
