## Note from 18/09/2022

This repository has been **archived**. I don't plan on maintaining it any longer, but I have made it public for the sake of documenting the work I have
done on it in the past.

---

# zetaml: a lightweight general-purpose maths library.

## Documentation

You can see the official documentation [here](https://kosude.github.io/zetaml/). The home page of that documentation is essentially mirrored in this README file.

## Summary

Zetaml is suitable for any C/C++ project that requires more complex mathematical functions and objects such as matrices, vectors, etc. Keep in mind that I am developing this project mainly for my own use, so the features here are really just the features I need for my other project(s). This is a personal project, not a professional one. But I still try to put effort into its documentation. 

## Usage

Zetaml is built with [CMake](https://cmake.org/).

When compiling, use the `-DZML_USE_FLOATS` flag to use floats (32-bit floating values) instead of doubles (64-bit floating values). You can also use the `-DZML_BUILD_TESTS` flag to build test executable(s); this can be useful if you intend to help develop zetaml. Furthermore, you can use the `i386-linux-gnu.cmake toolchain` file to build for 32-bit with GCC - as zetaml aims to be as compatible as possible with early architectures, I recommend testing the project on both x86 and x86_64 architectures if you contribute at all. *As a sidenote: if you do decide to contribute, please remember to test your contributions for memory leaks with [Valgrind](https://valgrind.org/).*

To use the library, include `<zetaml.h>`. 

## Naming scheme of operator functions

Zetaml operators are named systematically, and all work in order of left-to-right (i.e. `zmlDivideVecs_r(v1, v2)` is `v1 / v2`).

For example, `zmlAddVecs_r` adds two vectors and returns the result, allocating heap space for the resulting vector. The '\_r' comes from the fact that the function **r**eturns its result. Therefore, \_r operators are equivalent to '+', '-', '\*', etc.

However, `zmlAddVecs` adds v2 (its second argument) to v1 (its first argument), modifying v1. There is no '\_r' because nothing is returned. Therefore, \_r operators are equivalent to '+=', '-=', '\*=', etc.

When different types are operated on, they are all included in the function name, e.g. `zmlMultiplyVecMat()`.

Finally, logical operators are named based on the initials of each syllable, e.g. `zmlVecLT` is a **L**ess **T**han operator and `zmlMatGTE` is a **G**reater **T**han or **E**qual to operator. 
