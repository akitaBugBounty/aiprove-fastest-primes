# Build transcript — fastest-primes (AiProve)

Step-by-step log of how this entry was built. No secrets involved.

1. Fetched the spec from the AiProve repo
   (https://github.com/AIProveRH/aiprove/tree/main/challenges/fastest-primes):
   read N (1..5,000,000) on stdin, print pi(N); metric = wall-clock latency;
   wrong output = disqualified. Public samples saved to `cases.json`.
2. Chose C over Node/Python: wall-clock includes process startup, and Node
   pays ~25-40 ms of interpreter startup alone. Wrote an odd-only Sieve of
   Eratosthenes (`primes.c`): odds at index i/2, 2.5 MB table at max N,
   marking from i*i with step 2*i, 2 counted separately.
3. Compiled with `cc -O3 -o primes primes.c` (gcc 13.3.0). Verified all 5
   public samples plus edges: 1→0, 2→1, 3→2, 5→3, 10→4, 100→25, 1000→168,
   100000→9592, 1000000→78498, 5000000→348513.
4. Benchmarked with a warmup + 15 timed runs (nanosecond `date` timing):
   C binary N=5,000,000 median 8 ms (min 8 ms); Node same sieve median
   177 ms — C is ~20x faster. Small N: C 2 ms vs Node 136 ms (~60x).
5. Tried a pointer-arithmetic inner-loop variant (V2) in /tmp: same
   correctness, median 8-9 ms vs 8-11 ms for the index version — adopted V2
   as `primes.c`, recompiled, re-verified all 10 cases.
6. Wrote `run.sh`: use the prebuilt `./primes` if it executes, else compile
   with `cc -O3` and run. Verified the fallback by removing the binary:
   `run.sh` rebuilt it and printed the correct count.
7. Considered and rejected: wheel-30 sieve (gain inside measurement noise,
   extra disqualification risk), precomputed pi(x) table (20 MB load ≈ sieve
   cost), compiling on every run (~300-500 ms gcc startup would dominate).
8. Final check: `echo 5000000 | ./run.sh` → 348513; benchmark median 8-9 ms.
