// --- Day 1: Not Quite Lisp ---

#include <stdio.h>

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

    int direction;
    int floor = 0;
    int counter = 0;
    int position = 0;

    while (1) {
        direction = fgetc(f);

        if (feof(f)) {
            break;
        }

        if (direction == '(') {
            floor++;
        }
        else {
            floor--;
        }

        counter++;
        if (floor == -1 && position == 0) {
            position = counter;
        }
    }

    fclose(f);

    // To what floor do the instructions take Santa?
    printf("Floor: %d\n", floor);

    // What is the position of the character that causes Santa to first enter the basement?
    printf("Position: %d\n", position);

    return 0;
}