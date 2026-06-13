# Calc Projects

A series of five C projects that build on one another, starting from a one-line
command calculator and ending with a networked calculator service. Each project
reuses and extends ideas from the ones before it, gradually introducing file
handling, custom data structures, concurrency, and networking.

The projects are written in C (C11 minimum, C17 preferred) and built with CMake.
See each project's own README and reference document for full details.

## The Projects

### 1. SimpleCalc

A command-line calculator that evaluates a single expression and prints the
result. It takes two operands and an operator as arguments and performs the
arithmetic, establishing the core math and argument-parsing logic that the later
projects build on.

### 2. FileCalc

Extends the calculator to work with files. Instead of a single expression on the
command line, it reads equations from an input directory, evaluates each one, and
writes the solved results to an output directory. This introduces file parsing,
batch processing, and an expression evaluator.

### 3. DataStructures1

A set of reusable data structure libraries -- linked list, hash table, stack, and
queue -- each compiled as its own library and exercised by its own unit tests.
These structures are the building blocks used to manage work in the concurrency
project that follows.

### 4. ThreadCalc

Combines FileCalc with a thread pool to process work concurrently. Equation files
are queued as tasks (using the queue from the data structures project) and worked
by a configurable number of worker threads, producing the same output as FileCalc
but in parallel. This introduces threading, synchronization, and signal handling.

### 5. NetCalc

A client/server calculator. The server accepts connections and handles multiple
clients, receiving equation files over the network, evaluating them, and sending
results back. This brings the earlier work together over a network interface.

## Building and Testing

From the repository root:

```bash
bash build.sh          # build
bash build.sh debug    # build with address sanitizer and stricter checks
bash build.sh clean    # remove build artifacts
bash run_tests.sh      # build if needed, then run the full test suite
```

Each project can also be built on its own from inside its folder.

## Running the Tests

The test suite targets the **Ubuntu 20.04 toolchain** (gcc 9 / clang-tidy 10).
Newer compilers (gcc 14+ / clang 15+) promote several long-standing C warnings to
hard errors, so some projects will not build directly on an up-to-date host. To
get a reliable run regardless of your host, use the provided container, which
pins the expected toolchain:

```bash
sudo docker/run-tests.sh
```

This builds the image on first run (cached afterwards), then performs a clean
build and runs the full suite. Build artifacts stay owned by your user, not root.

The raw equivalent, if you prefer to run the steps yourself:

```bash
sudo docker build -t calc-projects-focal docker/
sudo docker run --rm -u "$(id -u):$(id -g)" -v "$PWD:/work" -w /work \
    calc-projects-focal bash -c 'bash build.sh clean && bash run_tests.sh'
```

To validate only the five canonical project tests (excluding the ThreadCalc
library's valgrind/helgrind memcheck tests):

```bash
sudo docker run --rm -u "$(id -u):$(id -g)" -v "$PWD:/work" -w /work \
    calc-projects-focal bash -c \
    'bash build.sh clean && bash build.sh && cd build && ctest -E "valgrind|helgrind" --output-on-failure'
```

## Test Status

All tests passed.

```console
ubuntu@ubuntu2004:~/Documents/calc-projects$ sudo docker/run-tests.sh
...
Running tests...
Test project /home/ubuntu/Documents/calc-projects/build
    Start 1: TestSimpleCalc
1/5 Test #1: TestSimpleCalc ...................   Passed    0.20 sec
    Start 2: TestFileCalc
2/5 Test #2: TestFileCalc .....................   Passed    0.47 sec
    Start 3: TestDataStructures1
3/5 Test #3: TestDataStructures1 ..............   Passed    3.29 sec
    Start 4: TestThreadCalc
4/5 Test #4: TestThreadCalc ...................   Passed    1.30 sec
    Start 5: TestNetCalc
5/5 Test #5: TestNetCalc ......................   Passed    2.75 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   8.01 sec
```
