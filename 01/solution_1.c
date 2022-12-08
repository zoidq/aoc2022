#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		perror("Unable to open input.txt");
		exit(1);
	}

	int maxCal = 0;
	int curCal = 0;
	char *line = NULL;
	size_t linecap = 0;
	while ((getline(&line, &linecap, fp)) > 0)
	{
		if (line[0] == '\n')
		{
			curCal = 0;
			continue;
		}

		curCal += atoi(line);
		if (curCal > maxCal)
		{
			maxCal = curCal;
		}
	}

	printf("max calories: %d\n", maxCal);
	;

	fclose(fp);
	return 0;
}
