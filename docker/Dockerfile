# Reproduce the CI / original toolchain: Ubuntu 20.04 ships gcc 9 and
# clang-tidy 10, where -Wint-conversion / -Wreturn-mismatch / etc. are
# WARNINGS (suppressed by the lint gate's `-checks=-*`) rather than the hard
# errors modern clang/gcc emit. This is what makes all 5 test suites pass.
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Union of the deps installed across the lint/build/test stages of gitlab-ci.yml,
# plus build-essential (the base image has no make/gcc).
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        python3 \
        libcunit1 \
        libcunit1-dev \
        clang-tidy \
        clang-format \
        valgrind \
        pylint \
        pycodestyle \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
