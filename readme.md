# Welcome to the cpp-utils library!

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![version](https://img.shields.io/badge/version-1.0.0-blue)

The `cpp-utils` project is a set of abstract C++ utilities that can be used in all types of projects. The repository provides all kind of traits,
containers, compile-time utilities and extensions to a few popular C++ libraries that has been implemented by the author in all sorts of projects
over the last few years.

# Content

The library divides source code into four submodules:

  - **estd**: extension of the standard library providing various traits, concepts and general utilities
  - **estl**: extension of the STL library
  - **lib-extensions**: code bas building up on top of popular platform-independent C++ libraries
  - **utilities**: auxiliary utilities that does not fall in any of previous categories

# Usage

To use the project, just download it and call `source source_me.bash update` file from the root directory of the project. This will install all
dependencies of the project. You can also set value of the `CPP_UTILS_INSTALL_BOOST_HEADERS` and `CPP_UTILS_INSTALL_CMAKE` variables in the 
`source_me.bash` file before to inform the script whether you need a custom installation of the boost headers. Next you can either install the CMake
project via:

    cmake \
        -B $CPP_UTILS_HOME/build \
        --install-prefix <prefix> \
        .
    cmake \
        --build $CPP_UTILS_HOME/build \
        --target install
    
or use it directly from the source tree by adding it as a subdirectory of your project with

    add_dubsirectory($ENV{CPP_UTILS_HOME})

`CPP_UTILS_HOME` will be automatically added to your environment every time you call `source source_me.bash` (not that sourcing `source_me.bash` without
an `update` argument will not trigger git to initialize submodule projects and so will save some time which is especially important if you set 
`CPP_UTILS_INSTALL_BOOST_HEADERS` to `true`). This call will also provide you terminal with utilities from 
[bash-utils](https://github.com/kpierczy/bash-utils) project that you should absolutely look at if you are used to write a lot of bash code!

Project provides a few CMake options that let you decide whether dependencies provided with the project should be included in the source tree 
(see [Dependencies](#dependencies)).

# Dependencies

Some parts of the library depend on external, open source libraries. These can be obtained from the relevant source repositories. However, original sources
may be not well-suited for some project environments (e.g. in embedded systems development). For this reason, the project provides custom versions of these
dependencies with a slightly modified source code that enables using them in most of the environments (especially embedded one)

## Boost

Some tools provided by the project depend on the boost library (header-only modules only). The project has been developed mainly in the embedded-systems
environment where the boost distribution is usually not present. For this reason, the library ships with a simple bash script automating 
from-[source](https://github.com/boostorg/boost) installation of boost headers into the source tree of the project. It also provides a custom target that 
will enable using these sources via CMake build system. To use this facility you need to set `CPP_UTILS_INSTALL_BOOST_HEADERS` variable in the 
`source_me.bash` file to true and call `source source_me.bash update` command from the root directory of the project. Next you need to set 
`WITH_CUSTOM_BOOST` CMake variable when building the project.

## boost-ext

The project provides some extensions for the series of libraries by Kris Jusiak available in the [boost-ext](https://github.com/boost-ext) repository
(it also utilizes boost-ext-ut library for unit testing). These libraries can be built automatically along with the project sources by enabling 
`WITH_CUSTOM_BOOST_EXT` CMake variable when building the project.

## mp-units

[mp-units](https://github.com/mpusz/units) library is an open source project by Mateusz Pusz providing extensive, compile-time-enabled support for physical
units in C++. The project is subject for future C++ standardization. Currently, it depends on a few open source libraries including
[fmt](https://github.com/fmtlib/fmt). For a few reasons the library and its dependencies cannot be compiled in some restricted environments (e.g. with
`-fno-exceptions` flag enabled). This is why the project provides customized version of its source code (along with dependencies) that can be built 
automatically along with the project sources by enabling `WITH_CUSTOM_MP_UNITS` CMake variable when building the project.
