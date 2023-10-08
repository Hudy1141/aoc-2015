// --- Day 5: Doesn't He Have Intern-Elves For This? ---

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool vowels(char *s)
{
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            count++;
            if (count == 3) return true;
        }
    }
    return false;
}

bool twice(char *s)
{
    for (int i = 0; i < 16; i++) {
        if (s[i] == s[i+1]) return true;
    }
    return false;
}

bool not(char *s)
{
    char *test;
    test = strstr(s, "ab");
    if (test != NULL) return false;
    test = strstr(s, "cd");
    if (test != NULL) return false;
    test = strstr(s, "pq");
    if (test != NULL) return false;
    test = strstr(s, "xy");
    if (test != NULL) return false;
    return true;
}

bool pair(char*s)
{
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (s[i] == s[i+j+2] && s[i+1] == s[i+j+3]) return true;
        }
    }
    return false;
}

bool repeat(char*s)
{
    for (int i = 0; i < 16; i++) {
        if (s[i] == s[i+2]) return true;
    }
    return false;
}

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

    char str[64];

    bool check_one = false;
    bool check_two = false;

    int count_one = 0;
    int count_two = 0;

    while (feof(f) == 0) {
        fgets(str, 64, f);

        check_one = vowels(str);
        if (check_one == true) check_one = twice(str);
        if (check_one == true) check_one = not(str);
        if (check_one == true) count_one++;

        check_two = pair(str);
        if (check_two == true) check_two = repeat(str);
        if (check_two == true) count_two++;
    }

    fclose(f);

    // How many strings are nice?
    printf("Nice strings: %d\n", count_one);

    // How many strings are nice under these new rules?
    printf("Nice strings: %d\n", count_two);

    return 0;
}