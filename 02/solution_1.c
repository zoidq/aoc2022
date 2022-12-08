#include <stdio.h>
#include <stdlib.h>

#define MOVE_ASCII_DIFF 23

void result(const int opponentMove, const int myMove, int *score)
{
    if ((opponentMove == 1 && myMove == 2) || (opponentMove == 2 && myMove == 3) || (opponentMove == 3 && myMove == 1))
        *score += 6;

    else if ((opponentMove == myMove))
        *score += 3;

    *score += myMove;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        perror("Unable to open input.txt");
        exit(1);
    }

    char *line = NULL;
    size_t linecap = 0;
    char opponentMove, myMove;
    int score = 0;
    while ((getline(&line, &linecap, fp)) > 0)
    {
        opponentMove = line[0] - 'A' + 1;
        myMove = line[2] - 'A' - MOVE_ASCII_DIFF + 1;
        result(opponentMove, myMove, &score);
    }

    printf("%d\n", score);
    return 0;
}