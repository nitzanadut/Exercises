#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: %s num num num num\n", argv[0]);
        exit(1);
    }

    unsigned int nums[4] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]) };
    unsigned int sum = 0;

    for (int i = 0; i < 4; i++) {
        sum += nums[i];
    }

    printf("%d", sum);
    return 0;
}