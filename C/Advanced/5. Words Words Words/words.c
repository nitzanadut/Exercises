#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 50
#define MAX 100

void numbers_to_words(char **numbers, int limit);
int count_letters(char *str);
void number_to_word(char *dest, int i);

int main() {
    char *numbers[MAX + 1];
    int sum = 0;

    // Init the array of char pointers
    for (int i = 0; i <= MAX; i++) {
        numbers[i] = (char*)malloc(MAX_STR * sizeof(char));
    }

    // Function call and summing up the letters
    for (int i = 0; i <= MAX; i++) {
        number_to_word(numbers[i], i);
        sum += count_letters(numbers[i]);
    }

    printf("%d\n", sum);
    return 0;
}

// Count the letters in a string
int count_letters(char *str) {
    char *ptr;
    int count = 0;

    for (ptr = str; *ptr != '\0'; ptr++) {
        if (isalpha(*ptr)) count++;
    }

    return count;
}

// Returns a string representing an integer
void number_to_word(char *dest, int i) {
    if (i == 0) {
        // Removing the - from numbers like twenty
        if (strlen(dest) > 0) 
            dest[strlen(dest) - 1] = '\0';
        return;
    }
    if (i < 10) {
        if (i == 1)      strcat(dest, "one");
        else if (i == 2) strcat(dest, "two");
        else if (i == 3) strcat(dest, "three");
        else if (i == 4) strcat(dest, "four");
        else if (i == 5) strcat(dest, "five");
        else if (i == 6) strcat(dest, "six");
        else if (i == 7) strcat(dest, "seven");
        else if (i == 8) strcat(dest, "eight");
        else if (i == 9) strcat(dest, "nine");
        return;
    } else if (i > 10 && i < 20) {
        if (i == 11)      strcat(dest, "eleven");
        else if (i == 12) strcat(dest, "twelve");
        else if (i == 13) strcat(dest, "thirteen");
        else if (i == 14) strcat(dest, "fourteen");
        else if (i == 15) strcat(dest, "fifteen");
        else if (i == 16) strcat(dest, "sixteen");
        else if (i == 17) strcat(dest, "seventeen");
        else if (i == 18) strcat(dest, "eighteen");
        else if (i == 19) strcat(dest, "nineteen");
        return;
    } else {
        if (i / 10 == 2)      strcat(dest, "twenty");
        else if (i / 10 == 3) strcat(dest, "thirty");
        else if (i / 10 == 4) strcat(dest, "fourty");
        else if (i / 10 == 5) strcat(dest, "fifty");
        else if (i / 10 == 6) strcat(dest, "sixty");
        else if (i / 10 == 7) strcat(dest, "seventy");
        else if (i / 10 == 8) strcat(dest, "eighty");
        else if (i / 10 == 9) strcat(dest, "ninety");
        else if (i == 100) {
            strcat(dest, "one hundred");
            return;
        }
        else {
            strcat(dest, "ten");
            return;
        }
    }

    strcat(dest, "-");
    number_to_word(dest, i % 10);
}