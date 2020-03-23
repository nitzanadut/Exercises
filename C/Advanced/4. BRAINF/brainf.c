#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 1000
#define MAX_PROG 2000

typedef struct Par {
    int start;
    int end;
} Par;

int group_pars(char code[MAX_PROG], int code_len, Par *pairs);
Par* find_Par(Par *pairs, int len_pairs, int index);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s file_name\n", argv[0]);
        exit(1);
    }

    // Init the data segment and the code segment
    int data_seg[MEM_SIZE];
    memset(data_seg, 0, MEM_SIZE);
    char code_seg[MAX_PROG];
    int *ptr = data_seg;
    int code_len = 0;

    FILE *brainf = fopen(argv[1], "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    if (brainf == NULL) {
        printf("Error opening the file!\n");
        exit(1);
    }

    // Reading the brainfuck code into code_seg
    while ((read = getline(&line, &len, brainf)) != -1) {
        char *current;
        for (current = line; *current != '\0'; current++) {
            if (*current == '<' || *current == '>' || *current == '+' || *current == '-' || *current == ',' || *current == '.' || *current == '[' || *current == ']')
                code_seg[code_len++] = *current;
        }
    }
    fclose(brainf);

    Par *pars = (Par*)malloc(code_len * sizeof(Par));
    int len_pars = group_pars(code_seg, code_len, pars);

    // Run the code
    for (int i = 0; i < code_len; i++) {
        char c = code_seg[i];
        if (c == '>') ++ptr;
        else if (c == '<') --ptr;
        else if (c == '+') {
            if (*ptr == 255) *ptr = 0; // Overflow
            else ++*ptr;
        }
        else if (c == '-') {
            if (*ptr == 0) *ptr = 255; // Underflow
            else --*ptr;
        }
        else if (c == ',') *ptr = getchar();
        else if (c == '.') putchar(*ptr);
        else if (c == '[' && !*ptr) i = find_Par(pars, len_pars, i)->end; // If the loop is complete jump to the end
        else if (c == ']') i = find_Par(pars, len_pars, i)->start - 1;  // Jump to the start of the loop and evaluate the condition
    }
}

// Groups the pairs of parentheses together
int group_pars(char code[MAX_PROG], int code_len, Par *pairs) {
    int stack[code_len];
    int stack_len = 0;
    int count = 0;
    memset(stack, -1, code_len);

    for (int i = 0; i < code_len; i++) {
        char current = code[i];
        if (current == '[') {
            stack[stack_len++] = i;
        } else if (current == ']') {
            if (stack_len == 0) return -1;
            pairs[count++].start = stack[--stack_len];
            pairs[count - 1].end = i;
        }
    }

    return count;
}

// Returns a pointer to an element in the pairs list that has the value index inside
Par* find_Par(Par *pairs, int len_pairs, int index) {
    for (int i = 0; i < len_pairs; i++) {
        Par *current = pairs + i;
        if (current->start == index || current->end == index)
            return current;
        current++;
    }
}
