#include<stdio.h>
// #include<conio.h>
#include<stdlib.h>
#include<string.h>

void failureFunction (char pattern [] , int lps []) {
    int patLen = strlen(pattern);
    int i = 1;
    int j = 0; 
    if (patLen > 0) lps[0] = 0;
    while(i < patLen) {
        if(pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else if(j > 0) {
            j = lps[j - 1];
        }
        else{
            lps[i] = 0;
            i++;
        }
    }
}

int kmpSearch(char text[], char pattern []) {
    int patternLength = strlen(pattern);
    int textLength = strlen(text);

    if (patternLength == 0) return 0;

    int lps[patternLength];
    failureFunction(pattern, lps);

    int i = 0;
    int j = 0;
    while (i < textLength) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == patternLength) {
                return i - j;
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1;
}

int main() {
    char text[1000];
    char pattern[100];
    
    printf("Enter a string as text:");
    scanf("%s", text);
    printf("Enter the string as pattern");
    scanf("%s", pattern);
    int position = kmpSearch(text, pattern);

    printf("%d", position);
}