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

    int houses_one = 1;
    int houses_two = 1;

    int direction;

    int santa_alone[2] = {0, 0};
    int santa[2] = {0, 0};
    int robot[2] = {0, 0};

    int turn = 0;

    int n = 1;

    int **map_alone = malloc(sizeof(int *) * n);
    map_alone[n-1] = malloc(sizeof(int) * 2);

    int **map = malloc(sizeof(int *) * n);
    map[n-1] = malloc(sizeof(int) * 2);

    map_alone[n-1][0] = santa_alone[0];
    map_alone[n-1][1] = santa_alone[1];

    map[n-1][0] = santa[0];
    map[n-1][1] = santa[1];

    while (1) {
        direction = fgetc(f);

        if (feof(f)) {
            break;
        }

        switch(direction) {
            case '^':
                santa_alone[1]++;
                (turn == 0) ? santa[1]++ : robot[1]++;
                break;
            case 'v':
                santa_alone[1]--;
                (turn == 0) ? santa[1]-- : robot[1]--;
                break;
            case '>':
                santa_alone[0]++;
                (turn == 0) ? santa[0]++ : robot[0]++;
                break;
            case '<':
                santa_alone[0]--;
                (turn == 0) ? santa[0]-- : robot[0]--;
                break;
        }

        n++;

        map_alone = realloc(map_alone, sizeof(int *) * n);
        map_alone[n-1] = malloc(sizeof(int) * 2);

        map = realloc(map, sizeof(int *) * n);
        map[n-1] = malloc(sizeof(int) * 2);

        for (int i = 0; i < n; i++) {
            if (map_alone[i][0] == santa_alone[0] && map_alone[i][1] == santa_alone[1]) {
                houses_one--;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            if (turn == 0) {
                if (map[i][0] == santa[0] && map[i][1] == santa[1]) {
                    houses_two--;
                    break;
                }
            }
            else {
                if (map[i][0] == robot[0] && map[i][1] == robot[1]) {
                    houses_two--;
                    break;
                }
            }
        }

        houses_one++;
        houses_two++;

        map_alone[n-1][0] = santa_alone[0];
        map_alone[n-1][1] = santa_alone[1];

        map[n-1][0] = (turn == 0) ? santa[0] : robot[0];
        map[n-1][1] = (turn == 0) ? santa[1] : robot[1];

        if (turn == 0)
            turn = 1;
        else
            turn = 0;
    }

    for (int i = 0; i < n; i++)
        free(map_alone[i]);
    free(map_alone);

    for (int i = 0; i < n; i++)
        free(map[i]);
    free(map);

    fclose(f);

    // How many houses receive at least one present?
    printf("Houses: %d\n", houses_one);

    // This year, how many houses receive at least one present?
    printf("Houses: %d\n", houses_two);

    return 0;
}