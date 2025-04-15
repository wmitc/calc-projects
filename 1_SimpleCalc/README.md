# Simple Calc #

Simple Calculator in C.

## How to
How to Use:
./simplecalc (operand1) (operator) (operand2)

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


## Known issues

Use of certain operands will be interpreted by the Unix command line as non-mathematical operations.

*  (*) must be preceded by a "\" or be encased in single quotes '*'
*  (<<) must be encased in single quotes '<<'
*  (>>) must be encased in single quotes '>>'
*  (<<<) must be encased in single quotes '<<<'
*  (>>>) must be encased in single quotes '>>>'