# Content
This folder contains fork of the source code of [mp-units](https://github.com/mpusz/units) library along with its dependencies [fmt](https://github.com/fmtlib/fmt) and [gsl-lite](https://github.com/gsl-lite/gsl-lite) packed together into a single, header-only CMake target. The aim of this construct is to provide capability to build this library along with Mbed build system that does not allow to compile external CMake projects using the same toolchain configuration (as current version of Mbed does not provide CMake toolchain files at all but rather configures compilation options on the fly when building the application)

# Versions
- `mp-units`: 0.7 with hot-fixes (git: ab351433ee6b20dfb548c1523607fd38569d53c4)
- `fmt`: 8.0.1 with hot-fixes (git: ec3b097cb98f1f50c6e9f7fd2ddfae885522de74)
- `mp-units`: 0.40.0 with hot-fixes (git: 4b5e9ab7474841fc2d7efc2e0064ef81785535d1)

# Modifications
The library contains some modifications to enable using it with Mbed (e.g. throws are changed into specific return values to eliminate exception). All changes are marked with `@modified` tag.
