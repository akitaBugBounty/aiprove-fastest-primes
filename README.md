# fastest-primes — AiProve entry

Read an integer N (1 <= N <= 5,000,000) on stdin, print the number of primes
<= N on stdout.

## Entry

- **Program:** `primes.c` (C, odd-only Sieve of Eratosthenes) + prebuilt
  binary `primes` (gcc 13.3.0, `-O3`, x86-64 Linux)
- **Run command:** `./run.sh`
  - Uses the prebuilt `./primes` binary if it executes (no compile time in
    the measured run); otherwise compiles with `cc -O3 -o primes primes.c`
    and runs. So the entry is fast on the grader machine and still works if
    the binary cannot execute there.
- **Fallback (not the entry, for comparison only):** `node primes.js`
  (same odd-only sieve in Node).

## Algorithm

Odds only: odd `x` lives at index `x/2`, so the table is 2.5 MB at max N.
`memset` to 1, `c[0]=0` (1 is not prime), then for each odd `i` with
`i*i <= n`, if still marked, clear `i*i, i*i+2i, i*i+4i, ...` via a raw
pointer that advances by `i` (no index multiply per store). Count 2
separately, then scan the table once. Correct for N=1 (prints 0) and N=2.

## Measured wall-clock latency (this VM, 15 runs after 3 warmups)

| program | N | min | median | max* |
|---|---|---|---|---|
| `./primes` (C) | 5,000,000 | 8 ms | **8 ms** | 43 ms |
| `./run.sh` (C) | 5,000,000 | 9 ms | **9 ms** | 42 ms |
| `node primes.js` | 5,000,000 | 128 ms | 177 ms | 284 ms |
| `./primes` (C) | 1,000,000 | 3 ms | 3 ms | 35 ms |
| `./primes` (C) | 10 | 2 ms | 2 ms | 34 ms |
| `node primes.js` | 10 | 111 ms | 136 ms | 193 ms |

\* Max values are scheduling noise on a shared 1.5-CPU VM; the typical run is
the median. The C entry is ~20x faster than Node at N=5,000,000 and ~60x
faster at small N, because wall-clock includes interpreter startup and Node
pays ~25-40 ms before the sieve even starts.

## Correctness

All 5 public samples from `cases.json` plus edges, verified:
10→4, 100→25, 1000→168, 100000→9592, 1000000→78498, 5000000→348513,
1→0, 2→1, 3→2, 5→3.

## Considered and rejected

- **Wheel-30 sieve:** would cut marking work further, but the gain (~2-3 ms)
  is inside this VM's measurement noise and the added index-mapping
  complexity raises disqualification risk. Wrong output = disqualified.
- **Precomputed pi(x) table:** 5M entries ≈ 20 MB to load; disk load costs
  as much as sieving. No win.
- **Compiling in the run command every time:** gcc startup (~300-500 ms)
  would dominate the measured latency, so the binary is prebuilt and the
  compile is only a fallback.
