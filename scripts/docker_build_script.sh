#!/bin/bash
mkdir /usr/src/builds

cd /usr/src/builds
mkdir build_amd64
cd build_amd64
cmake ../../code
make
cp sexpr_parser /usr/src/code/amd64_sexpr_parser

cd /usr/src/builds
mkdir build_aarch64
cd build_aarch64
cmake ../../code -DCMAKE_TOOLCHAIN_FILE=toolchains/aarch64.cmake
make
cp sexpr_parser /usr/src/code/aarch64_sexpr_parser

cd /usr/src/builds
mkdir build_arm32
cd build_arm32
cmake ../../code -DCMAKE_TOOLCHAIN_FILE=toolchains/arm.cmake
make
cp sexpr_parser /usr/src/code/arm32_sexpr_parser