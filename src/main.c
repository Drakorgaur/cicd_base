#include "main.h"
#include "stdio.h"

int main() {
    test(2, 'b');

    return 0;
}

int test(int a, char b) {
    printf("a: %d, b: %c", a, b);
    return 0;
}