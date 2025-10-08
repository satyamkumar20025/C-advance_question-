#include <stdio.h>

int term(int n, int a, int b, int c) {
    if (n == 1) return a;
    if (n == 2) return b;
    if (n == 3) return c;
    return term(n - 1, a, b, c) + term(n - 2, a, b, c) + term(n - 3, a, b, c);
}

int main() {
    int n, a, b, c;
    scanf("%d", &n);
    scanf("%d %d %d", &a, &b, &c);

    printf("%d\n", term(n, a, b, c));
    return 0;
}
