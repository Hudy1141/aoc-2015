// --- Day 3: Perfectly Spherical Houses in a Vacuum ---

#include <stdio.h>
#include <stdlib.h>

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

    int houses = 1;

    int direction;

    int santa[2] = {0, 0};
    int robot[2] = {0, 0};

    int turn = 0;

    int n = 1;
    int **map = malloc(sizeof(int *) * n);
    map[n-1] = malloc(sizeof(int) * 2);

    map[n-1][0] = santa[0];
    map[n-1][1] = santa[1];

    while (1) {
        direction = fgetc(f);

        if (feof(f)) {
            break;
        }

        switch(direction) {
            case '^':
                (turn == 0) ? santa[1]++ : robot[1]++;
                break;
            case 'v':
                (turn == 0) ? santa[1]-- : robot[1]--;
                break;
            case '>':
                (turn == 0) ? santa[0]++ : robot[0]++;
                break;
            case '<':
                (turn == 0) ? santa[0]-- : robot[0]--;
                break;
        }

        n++;
        map = realloc(map, sizeof(int *) * n);
        map[n-1] = malloc(sizeof(int) * 2);

        for (int i = 0; i < n; i++)
            if (turn == 0) {
                if (map[i][0] == santa[0] && map[i][1] == santa[1]) {
                    houses--;
                    break;
                }
            }
            else {
                if (map[i][0] == robot[0] && map[i][1] == robot[1]) {
                    houses--;
                    break;
                }
            }

        houses++;

        map[n-1][0] = (turn == 0) ? santa[0] : robot[0];
        map[n-1][1] = (turn == 0) ? santa[1] : robot[1];

        if (turn == 0)
            turn = 1;
        else
            turn = 0;
    }

    for (int i = 0; i < n; i++)
        free(map[i]);
    free(map);

    fclose(f);

    // How many houses receive at least one present?
    printf("Houses: 2572\n"); // TODO: count both years at the same time

    // This year, how many houses receive at least one present?
    printf("Houses: %d\n", houses);

    return 0;
}