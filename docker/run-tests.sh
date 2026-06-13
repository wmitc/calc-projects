#!/usr/bin/env bash
#
# Build and run the full test suite inside an Ubuntu 20.04 container, matching
# the toolchain the projects target. Use this instead of running build.sh /
# run_tests.sh directly when your host has a newer gcc/clang that promotes the
# old C warnings to hard errors.
#
# Usage:   docker/run-tests.sh            # build image (cached) + run all tests
#          docker/run-tests.sh shell      # drop into an interactive shell instead
#
# If your Docker daemon needs root, run with sudo; SUDO_UID/SUDO_GID below keep
# build artifacts owned by you rather than root.
set -euo pipefail

IMAGE=calc-projects-focal
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Map to the invoking user even under sudo, so the bind-mounted build/ and
# clanglog.txt aren't left root-owned on the host.
HOST_UID="${SUDO_UID:-$(id -u)}"
HOST_GID="${SUDO_GID:-$(id -g)}"

docker build -t "$IMAGE" "$SCRIPT_DIR"

if [[ "${1:-}" == "shell" ]]; then
    CMD=(bash)
else
    CMD=(bash -c 'bash build.sh clean && bash run_tests.sh')
fi

exec docker run --rm -it \
    -u "${HOST_UID}:${HOST_GID}" \
    -v "$REPO_ROOT:/work" \
    -w /work \
    "$IMAGE" \
    "${CMD[@]}"
