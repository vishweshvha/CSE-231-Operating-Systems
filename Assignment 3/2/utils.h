#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define PORT 2000
#define MAX_STRING_LENGTH 6  // Including NULL character.

struct StringEntry {
    int id_[5];
    char str_[5][MAX_STRING_LENGTH];
};

void generate_random_string(char *str, size_t length) {
    while (length-- > 1) {
        *str++ = (char) (rand() % 26) + 65;
    }
    *str = '\0';
}