# Simple Calc #

Simple Calculator in C.

## Overview

This is a  calculator application that will compute simple equations and produce the result.

### How to use

To compile, do either

```console
bash build.sh
```
OR
```console
make
```

To execute, from inside `1_SimpleCalc` directory:
```console
cd build

./simplecalc (operand1) (operator) (operand2)
```

For debugging:
```console
make debug
```

To validate with test suite from base folder (JQR CalcProjects/):
```console
bash build.sh 

bash run_tests.sh
```

To clean up:
```console
make clean
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

