#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

bool my_strstr(const char *s1, const char *s2);
bool is_substring(const char *s1, const char *s2);

int main() {
    printf("%d\n", my_strstr("Biss10", "Biss"));
    printf("%d\n", my_strstr("Biss", "Biss10"));
    printf("%d\n", my_strstr("Biss10", "TenBiss"));
    return 0;
}

// Check if s1 is a substring of s2 or vise versa
bool my_strstr(const char *s1, const char *s2) {
    return is_substring(s1, s2) || is_substring(s2, s1);
}

// Check if s2 is a substring of s1
bool is_substring(const char *haystack, const char *needle) {
    char *current;
    char *needle_current = NULL;
    
    // Iterating over the haystack and if a start of a needle is found, iterate over both the needle and the haystack
    for (current = haystack; *current != '\0'; current++) {
        if (needle_current == NULL && *current == *needle) {
            needle_current = needle;
        }

        if (needle_current != NULL) {
            if (*needle_current == '\0') { // Found an occurrence of needle in haystack, returning true
                return true;
            } else if (*needle_current != *current) { // That's a fake needle! keep on iterating
                needle_current = NULL;
            } else {
                needle_current++;
            }
        }
        
    }
    return false;
}