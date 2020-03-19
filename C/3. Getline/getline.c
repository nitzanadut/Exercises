#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>

/*
Hey, already solved this exercise a while ago, so I remember a little :)
Nitzan
*/

int size_t2int(size_t val);
size_t my_getline(char **buffer, size_t* size, FILE *stream);

int main() {
    size_t buf_size = 10;
    char *line = (char *)malloc(buf_size * sizeof(char));

    printf("%ld\n", my_getline(&line, &buf_size, stdin));
    printf("%s\n", line);

    return 0;
}

// This is my implemntation of the getline function
size_t my_getline(char **buffer, size_t* size, FILE *stream) {
    if (buffer == NULL) {
        exit(1);
    }

    int length = size_t2int(*size);
    char line[length];
    int characters;
    
    // Reading the line
    fgets(*buffer, length, stream);

    // Replacing newline with nullbyte
    char *current = strchr(*buffer,'\n');
    if (current)
        *current = '\0';

    characters = strlen(*buffer);

    // If we read less than 256 chars
    if (characters < length - 1) {
        current = realloc(*buffer, length);
        *buffer = current;
    }

    return characters;
}

int size_t2int(size_t val) {
    // Got this from StackOverFlow
    return (val <= INT_MAX) ? (int)((ssize_t)val) : -1;
}