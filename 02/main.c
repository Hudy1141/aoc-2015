// Day 2: I Was Told There Would Be No Math

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int paper(int l, int w, int h)
{
    int smallest_side = (l*w<w*h) ? (l*w<h*l?l*w:h*l) : (w*h<h*l?w*h:h*l);
    // before you ask, yes! I found this crazy expression on the internet
    return (2*l*w + 2*w*h + 2*h*l) + smallest_side;
}

int ribbon(int l, int w, int h)
{
    int longest_side = (l>w) ? (l>h?l:h) : (w>h?w:h);
    return 2 * ((l+w+h) - longest_side) + (l*w*h);
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

    char str[9];
    const char delim[2] = "x";
    char *token;

    int lenght;
    int width;
    int height;

    int total_paper = 0;
    int total_ribbon = 0;

    while (feof(f) == 0) {
        fgets(str, 9, f);

        token = strtok(str, delim);
        lenght = atoi(token);

        token = strtok(NULL, delim);
        width = atoi(token);

        token = strtok(NULL, delim);
        height = atoi(token);

        total_paper += paper(lenght, width, height);
        total_ribbon += ribbon(lenght, width, height);
    }

    fclose(f);

    //How many total square feet of wrapping paper should they order?
    printf("Paper: %d\n", total_paper);

    //How many total feet of ribbon should they order?
    printf("Ribbon: %d\n", total_ribbon);

    return 0;
}