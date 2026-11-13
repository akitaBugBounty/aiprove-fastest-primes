// Node fallback for comparison only (not the entry).
// Odd-only sieve with Uint8Array. Included to show why the C entry wins:
// Node pays ~25-40 ms of interpreter startup before the sieve even starts.
const fs = require('fs');
const n = parseInt(fs.readFileSync(0, 'utf8').trim(), 10);
if (n < 2) { console.log(0); process.exit(0); }
const m = (n + 1) >> 1;
const c = new Uint8Array(m).fill(1);
c[0] = 0;
for (let i = 3; i * i <= n; i += 2) {
  if (c[i >> 1]) for (let j = i * i; j <= n; j += 2 * i) c[j >> 1] = 0;
}
let cnt = 1;
for (let i = 1; i < m; i++) cnt += c[i];
console.log(cnt);
