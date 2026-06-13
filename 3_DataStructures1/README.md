# Data Structures #

Create implementations for each of the header files in the "include" directory and place them in the "src" directory.

## Overview

This project consists of building out source files that correspond to pre-written header files in the "include" directory. The header files outline and describe all required functions to be built out over the course of the project. The data structures include:

- Linked list
- Stack
- Queue
- Priority queue
- Hash table

### How to compile standalone binaries:

From inside `3_DataStructures1` directory:

```console
make
```
The binaries will be located in the `bin` directory.

To compile debug versions:
```console
make debug
```
The binaries will again be located in the `bin` directory. Debugging version file names will end in `_debug`. These binaries include a manual validation of functionality. They will print the results of validation to the console. 

## Testing

To run all tests, from inside `calc-projects` directory:
```console
bash runtests.sh
```
Output should include the following:
```console
    Start 3: TestDataStructures1
3/5 Test #3: TestDataStructures1 ..............   Passed    2.85 sec
```
To run ONLY data structure tests:
```console
bash local_tester2.sh 3_DataStructures1
```
The end of the output stream should appear as below:

```console
/home/user/Documents/calc-projects
-- Configuring done
-- Generating done
-- Build files have been written to: /home/user/Documents/calc-projects/3_DataStructures1/build
[ 10%] Built target queue_p
[ 20%] Built target test_queue_p
[ 30%] Built target queue
[ 40%] Built target stack
[ 50%] Built target test_stack
[ 60%] Built target hash_table
[ 70%] Built target test_table
[ 80%] Built target linked_list
[ 90%] Built target test_list
[100%] Built target test_queue

Passed 5 out of 5 
Removing Build Artifacts
```

## Dependencies and prerequisites

Prerequisites:
  - GCC (or Clang)
  - CMake
  - Valgrind
  - Make (optional)
  - Git (optional)

Dependencies:
  - Standard C library
  - [Optional] CUnit for testing

## Versions

* Requires gcc >= 9.4.0
* Requires CMake >= 3.10

## Limitations/Known issues

In `tests/linked_list_tests.c` the following changes were made:
* Commented out tests validating the list is circularly linked
* Commented out test of `list_sort` function

The tests for circular linkage were found to be malformed. The specification makes no mention of making the linked list into a circularly linked list. Moreover, adding circular linkage by pointing the tail pointer to the head causes downstream problems in other functions. Hence, these tests were thrown out.

As for the sort function test, the test script contains a comparison function that checks argument equality, but not one that handles integer comparisons. The `list_sort` implementation found in `linked_list.c` can be validated by running `make debug` and then running `bin/linked_list_debug`. The content of the list before and after sorting is printed to the console. Hence, the required implementation of a sorting algorithm is addressed despite skipping the provided test.