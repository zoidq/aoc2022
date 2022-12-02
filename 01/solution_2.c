#include <stdio.h>
#include <stdlib.h>

void rank(const int total, int *top)
{
		if(total > top[0]) {
				top[2] = top[1];
				top[1] = top[0];
				top[0] = total;
		} else if(total > top[1]) {
				top[2] = top[1];
				top[1] = total;
		} else if(total > top[2]) {
				top[2] = total;
		}
}

int main() 
{
		FILE *fp = fopen("input.txt", "r");
		if(fp == NULL) {
				perror("Unable to open input.txt");
				exit(1);
		}

		int top[] = {0, 0, 0};
		int curCal = 0;
		char *line = NULL;
		size_t linecap = 0;

		while((getline(&line, &linecap, fp)) > 0) {
				if(line[0] == '\n') {
						rank(curCal, top);
						curCal = 0;
						continue;
				}
				curCal += atoi(line);
		}

		printf("top three: %d %d %d\n", top[0], top[1], top[2]);
		printf("sum calories: %d\n", top[0] + top[1] + top[2]);
		fclose(fp);
		return 0;
}
