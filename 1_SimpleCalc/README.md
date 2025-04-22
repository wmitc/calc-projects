# Simple Calc #

Simple Calculator in C.

## Overview

This is a  calculator application that will compute simple equations and produce the result.

How to Use:

From inside `1_SimpleCalc` directory:
```console
bash build.sh 

cd build

./simplecalc (operand1) (operator) (operand2)
```

To validate from base folder:
```console
bash build.sh 

bash run_tests.sh
```

To clean up:
```console
rm -rf build 

rm -rf 1_SimpleCalc/build
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

Use of certain operands will be interpreted by the Unix command line as non-mathematical operations.

*  (\*) must be preceded by a "\\" or be encased in single quotes '\*' or it will be interpreted as a wildcard
*  (\&) must be preceded by a "\\" or be encased in single quotes '\*'
*  (\|) must be preceded by a "\\" or be encased in single quotes '\*'
*  (<<) must be encased in single quotes '<<'
*  (>>) must be encased in single quotes '>>'
*  (<<<) must be encased in single quotes '<<<'
*  (>>>) must be encased in single quotes '>>>'

