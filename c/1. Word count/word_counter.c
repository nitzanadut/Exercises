#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1000

int main() {
    FILE *aladin = fopen("aladin.txt", "r");
    int count = 0;
    
    if (aladin == NULL) {
        printf("Error opening the aladin.txt file\n");
        exit(1);
    }

    char line[MAX_LINE];
    char *token;
    while (fgets(line, MAX_LINE, aladin) != NULL) {
        token = strtok (line," ");
        char *c;
        while (token != NULL)
        {
            for (c = token; *c != '\0'; c++) {
                if (isalpha(*c)) {
                    count++;
                    break;
                }
            }
            token = strtok (NULL, " ");
        } 
    }

    printf("Aladin.txt has %d words.\n", count);

    return 0;
}