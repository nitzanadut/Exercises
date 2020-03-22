#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct Quadrangle {
    int height;
    int width;
    double area; // Has to be a full number
} Quadrangle;

int* rec2sqr(const Quadrangle *rect);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s height width\n", argv[0]);
        exit(1);
    }

    Quadrangle rect;
    rect.height = atoi(argv[1]);
    rect.width = atoi(argv[2]);
    rect.area = rect.height * rect.width;

    int *squares = rec2sqr(&rect);
    for (int i = 0; i < (int)rect.area; i++) {
        if (squares[i] == 0) break;
        printf("%d\n", squares[i]);
    }
}

// Recieves a rectangle and returns diameters of squares that will perfectly fill the rectangle
int* rec2sqr(const Quadrangle *rect) {
    int sum = 0;
    int count = 0;

    int current = floor(sqrt(rect->area));
    int *squares = (int *)malloc((int)rect->area * sizeof(int));
    memset(squares, 0, (int)rect->area);

    while (sum != (int)rect->area) {
        if (sum + floor(pow(current, 2)) > (int)rect->area) {
            current--;
        } else {
            sum += floor(pow(current, 2));
            squares[count++] = current;
        }
    }

    return squares;
}