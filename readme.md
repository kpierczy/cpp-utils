# Welcome to the cpp-utils library!

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![version](https://img.shields.io/badge/version-1.0.0-blue)

The `cpp-utils` project is a set of abstract C++ utilities that can be used in all types of projects. The repository provides all
kind of traits, containers, compile-time utilities and extensions to a few popular C++ libraries that has been implemented by the
author in all sorts of projects over the last few years.

# Content

The library divides source code into four submodules:

  - **estd**: extension of the standard library providing various traits, concepts and general utilities
  - **estl**: extension of the STL library
  - **lib-extensions**: code bas building up on top of popular platform-independent C++ libraries
  - **utilities**: auxiliary utilities that does not fall in any of previous categories

# Usage

To use the project, just download it and call `source source_me.bash update` file from the root directory of the project. This
will install all dependencies of the project. Next you can either install the CMake project via:

    cmake \
        -B $CPP_UTILS_HOME/build \
        --install-prefix <prefix> \
        .
    cmake \
        --build $CPP_UTILS_HOME/build \
        --target install
    
or use it directly from the source tree by adding it as a subdirectory of your project with

    add_dubsirectory($ENV{CPP_UTILS_HOME})

`CPP_UTILS_HOME` will be automatically added to your environment every time you call `source source_me.bash` (note that sourcing
`source_me.bash` without an `update` argument will not trigger git to initialize submodule projects and so will save some time).
This call will also provide you terminal with utilities from [bash-utils](https://github.com/kpierczy/bash-utils) project that you
should absolutely look at if you are used to write a lot of bash code!
