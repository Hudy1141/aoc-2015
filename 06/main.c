// --- Day 6: Probably a Fire Hazard ---

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x_start;
    int y_start;
    int x_end;
    int y_end;
} Coordinates;

Coordinates get_coordinates(char *s)
{
    Coordinates c;
    sscanf(s,"%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d", &c.x_start, &c.y_start, &c.x_end, &c.y_end);
    return c;
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

    int **grid = malloc(sizeof(int *) * 1000);

    for (int i = 0; i < 1000; i++)
        grid[i] = malloc(sizeof(int) * 1000);

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            grid[i][j] = 0;
        }
    }

    int **grid_copy = malloc(sizeof(int *) * 1000);

    for (int i = 0; i < 1000; i++)
        grid_copy[i] = malloc(sizeof(int) * 1000);

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            grid_copy[i][j] = 0;
        }
    }

    char str[33];

    Coordinates result;

    int lights = 0;
    int brightness = 0;

    while (feof(f) == 0) {
        fgets(str, 64, f);

        if (strstr(str, "on") != NULL) {
            result = get_coordinates(str);

            for (int i = result.x_start; i <= result.x_end; i++) {
                for (int j = result.y_start; j <= result.y_end; j++) {
                    grid[i][j] = 1;
                    grid_copy[i][j] += 1;
                }
            }
        }
        else if (strstr(str, "off") != NULL) {
            result = get_coordinates(str);

            for (int i = result.x_start; i <= result.x_end; i++) {
                for (int j = result.y_start; j <= result.y_end; j++) {
                    grid[i][j] = 0;
                    if (grid_copy[i][j] != 0) grid_copy[i][j] -= 1;
                }
            }
        }
        else {
            result = get_coordinates(str);

            for (int i = result.x_start; i <= result.x_end; i++) {
                for (int j = result.y_start; j <= result.y_end; j++) {
                    if (grid[i][j] == 0)
                        grid[i][j] = 1;
                    else
                        grid[i][j] = 0;
                    grid_copy[i][j] += 2;
                }
            }
        }
    }

    fclose(f);

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (grid[i][j] == 1)
                lights++;
            brightness += grid_copy[i][j];
        }
    }

    for (int i = 0; i < 1000; i++)
        free(grid[i]);
    free(grid);

    for (int i = 0; i < 1000; i++)
        free(grid_copy[i]);
    free(grid_copy);

    // After following the instructions, how many lights are lit?
    printf("Lights: %d\n", lights);

    // What is the total brightness of all lights combined after following Santa's instructions?
    printf("Brightness: %d\n", brightness);

    return 0;
}