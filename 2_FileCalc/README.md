# File Calc #

File parser in C. Expands on SimpleCalc project.

## Overview

This project consists of building a file parser. The format for input and output data follows a specific format as found in `FileSpec.pdf`. Given a directory containing `M` files, each with `N` equations, solve all equations. Write solutions per the specification to files in the output folder with the same name as their corresponding files from the input folder.

How to Use:

From inside `2_FileCalc` directory:
```console
bash build.sh 

cd build

mkdir input_dir output_dir

./filecalc <input_dir> <output_dir>
```

To validate from base folder:
```console
bash build.sh 

bash run_tests.sh
```

To clean up:
```console
rm -rf build 

rm -rf 1_FileCalc/build
```

Supported Operators:
*  (+) addition
*  (-) subtraction
*  (*) multiplication
*  (/) divide
*  (%) modulo
*  (<<) left shift
*  (>>) right shift
*  (&) and
*  (|) or
*  (^) xor 
*  (<<) left shift
*  (>>) right shift

Operands:
Negative numbers not accepted for bit related equations (<<, >>, &, |, ^, <<<, >>>)

## Dependencies and prerequisites

Prerequisites:
  - GCC (or Clang)
  - CMake
  - Make (optional)
  - Git (optional)

Dependencies:
  - Standard C library
  - Math library ("math_utils.h")
  - [Optional] CTest for testing

## Versions

* Requires CMake >= 3.10

## Limitations/Known issues

*  The spec states that all files should have permission bits set to `0644`, however, due to system defaults, the test script produces files with bits set to `0664`. Currently, permission bit validation is commented out in `process_file.c` so that the tests in the test suite pass. Files written to the output directory have `0644` bits set but this does not affect passing the tests since a validation check is not performed on these files.

