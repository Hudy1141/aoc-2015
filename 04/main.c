// --- Day 4: The Ideal Stocking Stuffer ---

#include <stdio.h>
#include <string.h>

#include "md5-c/md5.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Error: Missing argument\n");
        return -1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error");
        return -1;
    }

    char str[16];
    char string[16];

    int count = 1;

    uint8_t result[16];

    char hsh[64];
    char hash[64];
    hash[0] = '\0';

    int one = 0;
    int two = 0;

    while (1) {
        fgets(str, 16, f);
        sprintf(string, "%d", count);
        strcat(str, string);

        md5String(str, result);

        for (int i = 0; i < 16; ++i) {
            sprintf(hsh, "%02x", result[i]);
            strcat(hash, hsh);
        }

        int five = strncmp(hash, "00000", 5);
        int six = strncmp(hash, "000000", 6);

        if (five == 0 && one == 0) {
            one = count;
        }
        if (six == 0 && two == 0) {
            two = count;
            break;
        }

        count++;

        str[0] = '\0';
        string[0] = '\0';
        result[0] = '\0';
        hash[0] = '\0';

        rewind(f);
    }

    fclose(f);

    // The first hash that starts with five zeroes.
    printf("Five zeroes: %d\n", one);
    // The first hash that starts with six zeroes.
    printf("Six zeroes: %d\n", two);

    return 0;
}