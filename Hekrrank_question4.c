void update(int *a, int *b) {
    int sum = *a + *b;
    int diff = *a - *b;
    if (diff < 0) diff = -diff;

    *a = sum;
    *b = diff;
}
