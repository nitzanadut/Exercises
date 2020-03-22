#include <stdio.h>
#include <stdlib.h>

// Towers of Hanoi
void hanoi(char from, char other, char to, int disks) {
    if (disks == 0) {
        return;
    }

    hanoi(from, to, other, disks - 1);
    printf("Moved disk %d from %c to %c\n", disks, from, to);
    hanoi(other, from, to, disks - 1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s number_of_disks\n", argv[0]);
        exit(1);
    }

    hanoi('A', 'B', 'C', atoi(argv[1]));
}