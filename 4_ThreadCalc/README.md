# ThreadCalc & Threadpool Library

## Overview

In this project, we extend the functionality of FileCalc with a threadpool. This requires only small modifications to the file parser. A queue data structure is used (build during the DataStructures project).

### Basic Requirements

1. Written in C
2. Everything FileCalc does
3. Utilize a Threadpool to process work concurrently
4. Output files in the same way FileCalc does

### Specific Requirements

1. Utilize a data structure to manage work tasks
It is recommended that you use a data structure from DataStructures1
2. Utilize a Threadpool to process work from the data structure
3. Utilize getopt to process the following arguments
-n NUM (number of threads in the pool; defaults to 4)

# Tests

## Purpose
These tests are designed to test a general threadpool implementation either as part of the ThreadCalc project, or as a stand-alone threadpool library. As such, these tests do not check for integration with the rest of the Calculator Projects or some of the ThreadCalc tasks. 

## Building
### Dependencies
- C11 or higher, C17 preferred
- Clang-Tidy
- Valgrind
- CMake 3.16 or higher
- CUnit

```bash
sudo apt install clang-tidy valgrind cmake libcunit1 libcunit1-doc libcunit1-dev
```
Build the ThreadCalc executable and tests with the `build.sh` script from the root directory:

```zsh
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc$ bash build.sh 

-- The C compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
...
-- Configuring done
-- Generating done
-- Build files have been written to: /home/user/Documents/jqr-calcprojects/4_ThreadCalc/build
Scanning dependencies of target threadpool
[  5%] Building C object CMakeFiles/threadpool.dir/src/threadpool.c.o
...
[ 95%] Building C object CMakeFiles/threadcalc.dir/src/threadpool.c.o
[100%] Linking C executable ../bin/threadcalc
[100%] Built target threadcalc
```

Build only the ThreadCalc executable with `make` from the root directory (note: first create `bin` folder):

```zsh
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc$ mkdir bin
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc$ make

mkdir -p build
gcc -Iinclude -Wall -Wextra -g -pthread -c src/evaluate.c -o build/evaluate.o
mkdir -p build
gcc -Iinclude -Wall -Wextra -g -pthread -c src/threadpool.c -o build/threadpool.o
...
gcc -Iinclude -Wall -Wextra -g -pthread -o bin/threadcalc build/evaluate.o build/threadpool.o build/process_file.o build/queue.o build/threadcalc.o build/math_utils.o build/shared_mutex.o build/signals.o build/filejob.o build/file_io.o
rm -rf build/*.o
```

## Testing
The ThreadCalc tests check the functionality of critical threadpool functions and tasks, memory management and thread safety, and the memory management and thread safety of the standalone ThreadCalc executable.

### Signal Handling
The test suite also provides checks for a signal handler, which is not required to be integrated into the threadpool directly for testing purposes (refer to your project spec on implementation requirements), but can be if desired. If signal handling tests are not desired or implemented, modify the tests appropriately. Be aware, if signal handling is not implemented, a uncaught signal **will stop** the tests from proceeding unless modified.

### Running the Tests
The tests are integrated into the Gitlab CI/CD for your repo, and run automatically when a commit is pushed to the repo. The tests can also be run locally from the bin folder with `./test_threads`. This will run all tests built in the repo, including other projects:
```bash
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc/bin$ ./tests_threads 


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/


Suite: Thread Suite
  Test: test of threadpool_create() ...passed
  Test: test of add null pool ...[-] Pool or job do not exist.
passed
  Test: test of add null job ...[-] Pool or job do not exist.
[*] Job added to queue successfully
[*] Job added to queue successfully
passed
  Test: test of threadpool_add_job() ...[*] Job added to queue successfully
[*] Job added to queue successfully
[*] Job added to queue successfully
...
[*] Job added to queue successfully
[-] Can't add job, pool is shutdown.
[-] Can't add job, pool is shutdown.
FAILED
    1. /home/user/Documents/jqr-calcprojects/4_ThreadCalc/tests_src/thread_tests.c:353  - CU_ASSERT_EQUAL(*thread_check->entry_counter,DEFAULT_THREADPOOL_SIZE)
    2. /home/user/Documents/jqr-calcprojects/4_ThreadCalc/tests_src/thread_tests.c:366  - CU_ASSERT_EQUAL_FATAL(threadpool_add_job( pool_p, (job_f)check_thread_working, NULL, thread_check),ERROR)
Suite: Signal Handling Suite
  Test: test of signal handler() ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      2      2    n/a      0        0
               tests      7      7      6      1        0
             asserts     78     78     76      2      n/a

Elapsed time =    0.017 seconds
```
To run only the ThreadCalc tests from the root directory (python for functionality, valgrind and helgrind on the library tests):
```
user@optiplex:~/Documents/jqr-calcprojects$ bash local_tester.sh 4_ThreadCalc/

Start clang-tidy Check
No output here is good
Ignore "database" errors for now
...
[+] Operation complete. See ./threadcalc_tests/solved/63c71c6225b28107.equ for results.
[+] Shut down the threadpool
[+] Destroyed the threadpool
Test Results: Passed 16 out of 16 tests.
Removing Build Artifacts
```
```
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc/bin$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./threadcalc input_dir output_dir -n 5
```
```
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc/bin$ valgrind --tool=helgrind ./threadcalc input_dir output_dir -n 7
```


The test executable can also be run without valgrind and helgind:
```bash
user@optiplex:~/Documents/jqr-calcprojects/4_ThreadCalc/bin$ ./tests_threads
```
### Overall Status

Now the 4 four test suites pass (the 5th is erroneously passing as it is not yet implemented).

```
user@optiplex:~/Documents/jqr-calcprojects$ bash run_tests.sh 
Found build dir. Running tests...
Running tests...
Test project /home/user/Documents/jqr-calcprojects/build
    Start 1: TestSimpleCalc
1/5 Test #1: TestSimpleCalc ...................   Passed    0.16 sec
    Start 2: TestFileCalc
2/5 Test #2: TestFileCalc .....................   Passed    0.41 sec
    Start 3: TestDataStructures1
3/5 Test #3: TestDataStructures1 ..............   Passed    0.51 sec
    Start 4: TestThreadCalc
4/5 Test #4: TestThreadCalc ...................   Passed    1.18 sec
    Start 5: TestNetCalc
5/5 Test #5: TestNetCalc ......................   Passed    0.05 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   2.30 sec
```

## Known Issues
In the test output above we see:

```
Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      2      2    n/a      0        0
               tests      7      7      6      1        0
             asserts     78     78     76      2      n/a
```
Two assert statements failed within one test suite. After investigation, it was apparent theThese failures did not affect threadpool perfermorance when integrated with the FileCalc project.

## Note on Atomics
While C11 Atomics are thread safe, due to the instrumentation of the helgrind tool, they may show as a potential race condition in error output. There are a variety of techniques to address and suppress this output, but ultimately the trainee and reviewer should conduct a thorough review to ensure reported potential race conditions are not actually present.

## Additional Testing and Debugging Tools
These tests are conducted with valgrind, using the memcheck and helgrind tools. The valgrind DRD (Data Race Detector) can also be used for multithreaded program analysis. It tends to report fewer errors on atomics, but can have less clear error output. Additionally, the thread-sanitizer tool (a similar tool to Address Sanitizer) provides good debugging of data races.
