# ====================================================================================================================================
# @file       conanfile.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 28th December 2022 9:23:13 pm
# @modified   Wednesday, 1st March 2023 3:55:51 am
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

class CppUnitsConan(ConanFile):
    
    name        = "cpp-utils"
    license     = "MIT"
    author      = "Krzysztof Pierczyk"
    description = "Set of abstract C++ utilities that can be used in all types of projects."
    topics      = ("estl", "estd")
    homepage    = "https://github.com/kpierczy/cpp-utils"

    # ---------------------------------------------------------------------------- #

    minimal_cpp_std = "20"

    # ---------------------------------------------------------------------------- #
    
    settings = "os", "compiler", "build_type", "arch"

    # -------------------------------------------------------------------------
    # @note In Conan 2.0.0 components interface of the package_info()
    #    method is pretty buggy. For example it:
    #
    #      - requires test_requires dependencies to be required
    #        by components
    #      - for requires('boost') expectes that 'Boost::' will
    #        be referenced in package_info()
    #
    #    For these reasons the 'model_dependencies' options is temmporarly
    #    introduced to supress package failures. This should be removed from
    #    the recipe when the bugs are fixed.
    # -------------------------------------------------------------------------

    options = {
        "without_estd_preprocessor"    : [ True, False ],
        "without_boost_sml_extensions" : [ True, False ],
        "without_mp_units_extensions"  : [ True, False ],
        "model_dependencies"           : [ True, False ],
        "with_official_mp_units"       : [ True, False ],
    }

    default_options = {
        "without_estd_preprocessor"    : False,
        "without_boost_sml_extensions" : False,
        "without_mp_units_extensions"  : False,
        "model_dependencies"           : False,
        "with_official_mp_units"       : False,
    }

    default_options.update({ "boost/*:header_only" : True })

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
        
    @property
    def _with_estd_preprocessor(self):
        return not bool(self.options.without_estd_preprocessor)
        
    @property
    def _with_boost_sml_extensions(self):
        return not bool(self.options.without_boost_sml_extensions)
        
    @property
    def _with_mp_units_extensions(self):
        return not bool(self.options.without_mp_units_extensions)
        
    # ---------------------------------------------------------------------------- #

    def requirements(self):

        # Project requirements
        if self._with_estd_preprocessor or self._with_boost_sml_extensions or self._with_mp_units_extensions:
            self.requires("boost/1.81.0")
        if self._with_boost_sml_extensions:
            self.requires("sml/1.1.6")
        if self._with_mp_units_extensions:
            if self.options.with_official_mp_units:
                self.requires("mp-units/0.7.0")
            else:
                self.requires("mp-units/0.7.0@mpusz/stable")
            
        # Test requirements
        self.test_requires("boost-ext-ut/1.1.9")


    def validate(self):
        
        # Guarantee C++ standard
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self.minimal_cpp_std)


    def set_version(self):

        # Set version based on the CMakeLists.txt
        content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        version = re.search(r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)", content).group(1)
        self.version = version.strip()


    def layout(self):
        cmake_layout(self)


    def generate(self):

        toolchain = CMakeToolchain(self)

        # Create CMake toolchain
        toolchain.generate()
        # Forward options to the CMake
        toolchain.variables['WITH_ESTD_PREPROCESSOR'   ] = self._with_estd_preprocessor or \
                                                           self._with_boost_sml_extensions or \
                                                           self._with_mp_units_extensions
        toolchain.variables['WITH_BOOST_SML_EXTENSIONS'] = self._with_boost_sml_extensions
        toolchain.variables['WITH_MP_UNITS_EXTENSIONS' ] = self._with_mp_units_extensions

        deps = CMakeDeps(self)

        # Generate dependencies for the CMake scripts
        deps.generate()


    def build(self):
        
        cmake = CMake(self)

        # Build project
        cmake.configure()
        cmake.build()
        # Test project
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()


    def package(self):

        # Install license
        copy(self, "license", self.source_folder, os.path.join(self.package_folder, "licenses"))
        # Install binaaries according to the CMake
        cmake = CMake(self)
        cmake.install()


    def package_info(self):

        if not self.options.model_dependencies:
            return

        def requires_if(name, condition):
            return ([ name ] if condition else [ ])

        # Extended STD
        self.cpp_info.components[ "estd" ].libdirs  = [ ]
        self.cpp_info.components[ "estd" ].requires = [
            *requires_if("Boost::headers", self._with_estd_preprocessor)
        ]
        
        # Extended STL
        self.cpp_info.components[ "estl" ].libdirs  = [ ]
        self.cpp_info.components[ "estl" ].requires = [
            "estd"
        ]
        
        # Libraries extensions
        self.cpp_info.components[ "boost-sml-ext" ].libdirs  = [ ]
        self.cpp_info.components[ "boost-sml-ext" ].requires = [
            "estd",
            *requires_if("sml::sml", self._with_boost_sml_extensions)
        ]
        self.cpp_info.components[ "mp-units-ext" ].libdirs  = [ ]
        self.cpp_info.components[ "mp-units-ext" ].requires = [
            "estd",
            *requires_if("mp-units::mp-units", self._with_mp_units_extensions)
        ]

        # Utilities
        self.cpp_info.components[ "utilities" ].libdirs  = [ ]
        self.cpp_info.components[ "utilities" ].requires = [
            "estd"
        ]


# ================================================================================================================================== #
