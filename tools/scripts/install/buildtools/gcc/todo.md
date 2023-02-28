# GCC Toolchain builder

At the moment pair of `gcc.bash` and `gcc-arm-none-eabi.bash` scripts is a more user- and update-friendly version of the building 
script [ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
(version 10.3-2021.10). These was designed to provide an easy way to build embedded toolchains in the future featuring the newest version of GCC
(and so the newest version of C++ standard library). Said so they are flexible and convinient for this particular purpose. However building other
kind of toolchains (e.g. naitive) may require some dirty and unconvinient tricks. For this reason it is a good idea to think-through the whole
framework's structure and recompose it to provide a unified API for building all kind of GCC-based toolchains. Underlying section provide some
insights in potential changes

## GMP, MPC, MPFR and other dependencies

At the moment all libraries required by the GCC are built in external directories and linked at build time with the GCC. This is not an obstacle
when it comes to the usage of the embedded toolchain as it usually uses only statically-linked libraries. However, for native toolchains the 
standard usage foresees fully dynamic linkage. In such a scenario, the dependant libraries must have been present on the search path of linker.
It would be good idea to give user a choice between off-the-tree libraries' build and in-tree build. In the secend scenario the option to go is 
GCC-provided `./contrib/download_prerequisites` script that downloads required dependencies directly into the GCC's tree. This discards problems
with dynamic linkage when using a built toolchain. In general approach to dependencies should be rethought. Good sources are:

- [GCC official installation guide](https://gcc.gnu.org/wiki/InstallingGCC)
- [Linux from scratch tutorial](https://www.linuxfromscratch.org/lfs/view/stable/chapter08/chapter08.html)

At the moment all dependancies are built in the bulk. It is good idea to provide user with choice between building off-the-tree dependencies 
(potentially only some of them) and using in-tree dependencies

## Build staging (partially solved)

At the moment toolchain's build is performed in seven stages:

1. dependencies
    - zlib
    - gmp
    - mpfr
    - mpc
    - isl
    - libelf
    - expat
2. binutils
3. gcc compiler
4. libc
    - newlib
    - newlib-nano
5. libgcc
6. libc++
7. gdb

These are closely fixed and only small variantions are available (e.g. one may resign from building gdb or binutils), but GCC's and
libc's builds are closely coupled. This is not a problem in embedded world where such a scheme is broadly met (compiler is always built
along with the libc as the later is required to finalize libc++ that is part of the GCC). However this is not a case in native world.
The `checkbox` mechanism shall be modified to make it possible to build both parts independently.

## Customization

With hight degree of certainty, the script's writer cannot forecast all usecases of potential users. As so it is desired to provide high
level of building process' customization. One idea is to provide optional user-defined `handlers` called before/after building of each 
component. Such handler could be implemented with bash `functions` and would play nicely with definitions-injecting mechanism provided by
`TOOLCHAIN_EVAL_STRING` environmental argument. 

## Choice of the libc implementation (partially solved)

At the moment choice of the libc implementation is limited to `newlib`/`newlib-nano`. It may be potentially extended to other libraries
but current mechanism of resolving libc's name drastically limtis such a possibility. One of main aims for future development should be
unifying building interface with respect to libc implementation's choice. 

[1] A good idea would be to provide separate option switches for choosing versions of supported implementations (at the moment a single
switch - --libc-version - is provided which requires complicated names resolution in down-stream parts of the framework)
