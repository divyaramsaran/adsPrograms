#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_CHARS 256

void badCharHeuristic(char *pattern, int patternLength, int badchar[NO_OF_CHARS]) {
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < patternLength; i++)
        badchar[(int)pattern[i]] = i;
}

void boyerMoore(char *text, char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pattern, patternLength, badchar);

    int shift = 0;

    while (shift <= (textLength - patternLength)) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", shift);
            shift += (shift + patternLength < textLength) ? patternLength - badchar[text[shift + patternLength]] : 1;
        }
        else {
            int badCharShift = j - badchar[text[shift + j]];
            shift += (badCharShift > 0) ? badCharShift : 1;
        }
    }
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter the text: ");
    scanf("%s", text);
    
    printf("Enter the pattern to search: ");
    scanf("%s", pattern);
    
    printf("\nSearching for pattern in the text...\n");
    boyerMoore(text, pattern);
    
    return 0;
}