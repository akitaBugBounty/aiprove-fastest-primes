#!/bin/sh
# Run command for fastest-primes.
# Prefer the prebuilt binary (fast: no compile time in the measured run).
# If it is missing or cannot execute on this machine, build it, then run.
./primes 2>/dev/null || { cc -O3 -o primes primes.c && ./primes; }
