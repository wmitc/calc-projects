# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

A repo of five progressive C projects. Each builds on the
previous, so source files like `math_utils.c`, `evaluate.c`, and `process_file.c` are
copied forward and evolved per project rather than shared via a common library:

1. `1_SimpleCalc` — CLI calculator: `simplecalc <operand1> <operator> <operand2>`
2. `2_FileCalc` — reads equation files from an input dir, writes solved files to an output dir
3. `3_DataStructures1` — linked list / hash table / stack / queue libraries, tested with CUnit
4. `4_ThreadCalc` — FileCalc + a threadpool (uses the queue from project 3); `-n NUM` threads (default 4)
5. `5_NetCalc` — client/server (poll-based) that sends equation files over the network

Each project is self-contained with its own `CMakeLists.txt`, `Makefile`, `build.sh`,
`src/`, `include/`, and a spec PDF under `references/`. `0_Common` is a shared-code slot
that is currently empty.

## Build & test

Run from the repo root.

```bash
bash build.sh          # release build (cmake + make into ./build)
bash build.sh debug    # -fsanitize=address, -Werror, clang-tidy errors fatal
bash build.sh test     # build in test mode then run ctest
bash build.sh clean    # remove ./build and each project's bin/
bash run_tests.sh      # build if needed, then `make test` (ctest) in ./build
```

Run a single project's test suite directly (the same thing each ctest case invokes):

```bash
bash local_tester.sh 1_SimpleCalc   # arg is the project folder name
```

`local_tester.sh` first runs `clang-tidy` over the project's `*.c`/`*.h` and **fails on any
non-NOLINT warning**, then runs the matching `Tests/<Name>Tests.py`. Test names map by
stripping the numeric prefix: `1_SimpleCalc` → `Tests/SimpleCalcTests.py`.

Each project can also be built standalone from inside its folder with `bash build.sh` or
`make` (see the project README).

## How the build/test wiring fits together

- **Top-level `CMakeLists.txt`** only `add_subdirectory`s projects that are enabled — note
  `4_ThreadCalc` and `5_NetCalc` are currently commented out there, and `3_DataStructures1`
  is added but builds nothing unless its `src/*.c` files exist (the `CMakeLists.txt` guards
  each target with `if(EXISTS ...)`). So a clean `build.sh` compiles SimpleCalc and FileCalc.
- **`main.cmake`** (included by the top-level) defines build-type flags. `debug` adds
  ASan + `-Werror` + clang-tidy with `-warnings-as-errors=*`; `test` builds with `-g` and
  enables ctest; default/release is plain `-Wall -Wextra -pedantic`.
- **ctest** does not compile the calculators — each `add_test` runs `local_tester.sh`, and
  the `Tests/*.py` harnesses invoke the already-built binaries (e.g. FileCalc's test runs
  `./build/2_FileCalc/filecalc ...`). The Python tests under `Tests/` generate equation
  files, run the binary, and grade output via `EquGrader.py` / `EquFileGen.py`.

## Linting (must pass; enforced in CI via `.gitlab-ci.yml`)

- C formatting: `clang-format --dry-run -Werror --style=file` (config in `.clang-format`)
- Python: `pylint` and `pycodestyle` over the project folder
- `clang-tidy` as described above

ThreadCalc additionally has CUnit-based C tests and is run under valgrind/helgrind in CI.

## Conventions

- C11 minimum, C17 preferred. Keep to the existing `src/` + `include/` layout per project.
- This repo targets GitLab (`code.levelup.cce.af.mil`); each project is developed on its own
  branch and merged to `main` when ready for review.
- Build artifacts (`build/`, `bin/`, `*.o`) and committed binaries appear in the tree but
  `build/` is gitignored; don't add new build products.
