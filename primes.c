// V2: pointer-arithmetic inner loop (no index multiply per store).
#include <stdio.h>
#include <string.h>
static unsigned char c[2500001];
int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 2) { printf("0\n"); return 0; }
    int m = (n + 1) / 2;
    memset(c, 1, m);
    c[0] = 0;
    unsigned char *end = c + m;
    for (int i = 3; (long)i * i <= n; i += 2) {
        if (c[i / 2]) {
            unsigned char *p = c + (i * i) / 2;
            for (; p < end; p += i) *p = 0;
        }
    }
    int cnt = 1;
    for (int i = 1; i < m; i++) cnt += c[i];
    printf("%d\n", cnt);
    return 0;
}
