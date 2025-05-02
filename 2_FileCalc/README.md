# File Calc #

File parser in C. Expands on SimpleCalc project.

## Overview

This project consists of building a file parser. The format for input and output data follows a specific format as found in `FileSpec.pdf`. Given a directory containing `M` files, each with `N` equations, solve all equations. Write solutions per the specification to files in the output folder with the same name as their corresponding files from the input folder.

### How to use:

From inside `2_FileCalc` directory:

```console
make
```
OR
```console
bash build.sh 
```

Then:


```console
cd build

mkdir input_dir output_dir

cd input_dir

python ../../EquFileGen.py

cd ..

./filecalc <input_dir> <output_dir>
```

You should see output like this:

```console
[+] Operation complete. See output_dir/f01709749f1a1f3a.equ for results.
[+] Operation complete. See output_dir/cd2b3f5b03796807.equ for results.
[+] Operation complete. See output_dir/2feb07cfd1bae2c8.equ for results.
[+] Operation complete. See output_dir/9189ecb10121e47a.equ for results.
[+] Operation complete. See output_dir/beca8284bf9b7d0d.equ for results.
[+] Operation complete. See output_dir/08ccedf7c43a0636.equ for results.
[+] Operation complete. See output_dir/e35beb95e4f18e54.equ for results.
[+] Operation complete. See output_dir/04531d9f9cdf15c3.equ for results.
[+] Operation complete. See output_dir/8540a7248b4d6b81.equ for results.
[+] Operation complete. See output_dir/d634287cb0ec6db5.equ for results.
[+] Operation complete. See output_dir/4aca3b6cd24c3eb5.equ for results.
[+] Operation complete. See output_dir/6503956feaed909e.equ for results.
[+] Operation complete. See output_dir/fb18e029d01e2e87.equ for results.
[+] Operation complete. See output_dir/a72a3301d97563f7.equ for results.
[+] Operation complete. See output_dir/db7e7977505666df.equ for results.
[+] Operation complete. See output_dir/275961cd50cb3c44.equ for results.
```

To aid debugging:
```console
make debug
```

To clean up:
```console
make clean
```

To run test suite from base folder:
```console
bash build.sh

bash run_tests.sh
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

