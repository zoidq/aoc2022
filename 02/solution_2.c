#include <stdio.h>
#include <stdlib.h>

void result(const char opponentMove, const char outcome, int *score)
{
    switch (outcome)
    {
    case 'X':
        switch (opponentMove)
        {
        case 'A':
            *score += 3;
            break;
        case 'B':
            *score += 1;
            break;
        case 'C':
            *score += 2;
            break;
        }
        break;

    case 'Y':
        *score += 3 + (opponentMove - 'A') + 1;
        break;

    case 'Z':
        switch (opponentMove)
        {
        case 'A':
            *score += 2;
            break;
        case 'B':
            *score += 3;
            break;
        case 'C':
            *score += 1;
            break;
        }
        *score += 6;
    }
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
    int score = 0;
    while ((getline(&line, &linecap, fp)) > 0)
    {
        result(line[0], line[2], &score);
    }

    printf("%d\n", score);
    return 0;
}