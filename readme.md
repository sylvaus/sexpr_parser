S-expression parser
===================
[![Build Status](https://travis-ci.org/sylvaus/sexpr_parser.svg?branch=master)](https://travis-ci.org/sylvaus/sexpr_parser)


Implementation of an S-expression parser


Dev Environment
---------------
* WSL2 Ubuntu 18.04


Requirements
------------
* The parser shall take one single input which is the path to a file containing the S-expression to parse
* The parser shall print the parsed S-expression in a nested way representing the lists and each atom should be printed with its datatype

Assumptions
------------
* The parser is implemented based on the syntax described on [Wikipedia](https://en.wikipedia.org/wiki/S-expression)
* The parser only supports the following datatypes: Lists, Symbols, Strings, Integers, Floating-point numbers
* The parser only handles integer which fit in int64_t
* The parser only handles floating-point numbers which fit in a double
* The first version of the parser won't support the [cons notation](https://en.wikipedia.org/wiki/Cons) e.g. (x . y)

Approach
--------
The approach taken is similar to the one used for parsing a programming language.
First a tokenization/lexing is done to get a list of string with a meaning and then 
the parsing is done on the generated token to generate the desired output


Compilation
-----------
Tested on: WSL Ubuntu 18.04, g++ 7.5.0

Pre-requisites:
* g++
* cmake
* (optional for test only) [gtest](https://github.com/google/googletest/blob/master/googletest/README.md): install from source version 1.10.0

Download and unzip or git clone this repository
Run the following commands in the sexpr_parser folder:
* `mkdir build && cd build`
* `cmake ..` or `cmake .. -DTESTS=1` if you have gtest and want to run the tests
* `make`

Optional: Run test
* `./tests`


arm64 Cross-Compilation
-----------------------
Tested on: WSL Ubuntu 18.04 (compilation) / RPI 3B (execution)

Pre-requisites:
* cmake
* crossbuild-essential-arm64

Download and unzip or git clone this repository
Run the following commands in the sexpr_parser folder:
* `mkdir build && cd build`
* `cmake .. -DCMAKE_TOOLCHAIN_FILE=toolchains/aarch64.cmake` 
* `make`

arm32 Cross-Compilation
-----------------------
Tested on: WSL Ubuntu 18.04 (compilation) / qemu-arm (execution: qemu-arm sexpr_parser filepath)
If you get the following error when trying to run with qemu-arm: `/lib/ld-linux-armhf.so.3: No such file or directory`
You may have to use the following command: `export QEMU_LD_PREFIX=/usr/arm-linux-gnueabihf` [source](https://ownyourbits.com/2018/06/13/transparently-running-binaries-from-any-architecture-in-linux-with-qemu-and-binfmt_misc/) 

Pre-requisites:
* cmake
* crossbuild-essential-arm32

Download and unzip or git clone this repository
Run the following commands in the sexpr_parser folder:
* `mkdir build && cd build`
* `cmake .. -DCMAKE_TOOLCHAIN_FILE=toolchains/arm.cmake` 
* `make`


Usage 
-----
`./scexpr_parser <filepath>`
* filepath should be a valid path to a text file containing the S-expression to parse


TODO
----
* Add docstrings
* Implement the functional version 
* Implement the minimal viable product version
* Add benchmark to see the best implementation for a given situation
* Implement proper handling of invalid S-epression
* Add coverall on the UT
* Improve the Unit-testing


Resources
----------
* [Wikipedia S-expression](https://en.wikipedia.org/wiki/S-expression)
* [Wikipedia Cons Notation](https://en.wikipedia.org/wiki/Cons)
* [Example of S-expression parser](https://rosettacode.org/wiki/S-Expressions)
* [Possible origin of the challenge](https://github.com/Spaceless007/SEXP-Parser)





