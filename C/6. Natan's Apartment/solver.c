#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* get_index(char keypad[4][3], char key);
char* get_neighbors(char keypad[4][3], char key);
int char_count(char *str, char ch);
int check_combo(char *combo, char *code, char keypad[4][3]);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s code", argv[0]);
        exit(1);
    }

    char keypad[4][3];
    char *code = argv[1];
    
    // Initialization
    keypad[0][0] = '1'; keypad[0][1] = '2'; keypad[0][2] = '3';
    keypad[1][0] = '4'; keypad[1][1] = '5'; keypad[1][2] = '6';
    keypad[2][0] = '7'; keypad[2][1] = '8'; keypad[2][2] = '9';
    keypad[3][0] = ' '; keypad[3][1] = '0'; keypad[3][2] = ' ';

    // Configure neighbors
    char *neighbors[strlen(code)];
    for (int i = 0; i < strlen(code); i++) {
        neighbors[i] = get_neighbors(keypad, code[i]);
    }

    // Configure a current key combo variable
    int i, j;
    char combo[strlen(code) + 1];
    combo[strlen(code)] = '\0';
    for (i = 0; i < strlen(code); i++) combo[i] = '0';
    
    // Brute-Force the key
    while (char_count(combo, '9') != strlen(code)) {
        if (check_combo(combo, code, keypad) == 0) {
            printf("%s\n", combo);
        }

        if (combo[strlen(code) - 1] == '9') {
            for (i = strlen(code) - 2; i >= 0; i--) {
                if (combo[i] != '9') {
                    combo[i]++;
                    for (j = strlen(code) - 1; j != i; j--) combo[j] = '0';
                    break;
                }
            }
        } else {
            combo[strlen(code) - 1]++;
        }
    }
}

// Returns whether combo is a valid key combo to unlock keypad
int check_combo(char *combo, char *code, char keypad[4][3]) {
    char *current;

    for (int i = 0; i < strlen(combo); i++) {
        char current = combo[i];
        char *neighbors = get_neighbors(keypad, code[i]);
        char *neighbor;
        int in = 0;
        for (neighbor = neighbors; *neighbor != '\0'; neighbor++) {
            if (current == *neighbor) in = 1;
        }
        if (in == 0) return 1;
        in = 0;
    }
    return 0;
}

// Returns the amount of times ch is in str
int char_count(char *str, char ch) {
    char *current;
    int count = 0;

    for (current = str; *current != '\0'; current++) {
        if (*current == ch)
            count++;
    }

    return count;
}

// Returning the x and y position of a key on the keypad
int* get_index(char keypad[4][3], char key) {
    int *pos = (int *)malloc(2 * sizeof(int));
    pos[0] = pos[1] = -1;
    char current;

    for (int i = 0; i < 4; i++) {
        char *line = keypad[i];
        for (int j = 0; j < 3; j++) {
            current = line[j];
            if (current == key) {
                pos[0] = i;
                pos[1] = j;
                return pos;
            }
        }
    }

    return pos;
}

// Given a key on the keypad, return a string representing all the keys that are neighbors of key and key itself
char* get_neighbors(char keypad[4][3], char key) {
    if (key == '0') {
        char *zero_neighbors = (char *)malloc(2 * sizeof(char));
        zero_neighbors[0] = '8';
        zero_neighbors[1] = '0';
        return zero_neighbors;
    }

    int count = 4;
    int *pos = get_index(keypad, key);
    
    if      (pos[0] == 0) count--;
    else if (pos[0] == 3) count--;
    if      (pos[1] == 0) count--;
    else if (pos[1] == 2) count--;

    char *neighbors = (char *)malloc((count + 1) * sizeof(char));
    
    neighbors[count--] = key;

    if (pos[0] == 0 && pos[1] == 0) {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] + 1];
    } else if (pos[0] == 0 && pos[1] == 2) {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] - 1];
    } else if (pos[0] == 0) {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] - 1];
        neighbors[count--] = keypad[pos[0]][pos[1] + 1];
    } else if (pos[1] == 0) {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0] - 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] + 1];
    } else if (pos[1] == 2) {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0] - 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] - 1];
    } else {
        neighbors[count--] = keypad[pos[0] + 1][pos[1]];
        neighbors[count--] = keypad[pos[0] - 1][pos[1]];
        neighbors[count--] = keypad[pos[0]][pos[1] - 1];
        neighbors[count--] = keypad[pos[0]][pos[1] + 1];
    }

    return neighbors;
}
