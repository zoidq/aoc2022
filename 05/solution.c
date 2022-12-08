#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKS 9
#define GRID_HEIGHT 7
#define GRID_WIDTH 35
#define MAX_SIZE 64

typedef struct Stack {
	int count;
	char items[MAX_SIZE];
} Stack;

typedef struct Cargo {
	Stack stack[STACKS];	
	int limit;
} Cargo;

void move(Cargo *cargo, const int quantity, const int from, const int to) 
{
	char *src = cargo->stack[from-1].items;
	char *dst = cargo->stack[to-1].items;
	int crates = 1;
	if(!cargo->limit)
		crates = quantity;

	for(int i = 0; i < quantity; i += crates) {
		memmove(dst+crates, dst, strlen(dst));
		memcpy(dst, src, crates);
		memmove(src, src+crates, strlen(src));
	}
}

void parseInitialGrid(Cargo *cargo, FILE *fp, char *line, size_t *len) 
{
	char item;
	int c = 0, i, index;

	while((getline(&line, len, fp) > 0) && (c++ <= GRID_HEIGHT)) {
		index = 0;
		for(i = 1; i < GRID_WIDTH; i += 4) {
			item = line[i];
			if(item != ' ') 
				strncat(cargo->stack[index].items, &item, 1);
			index ++;
		}
	}
}

void processInstructions(Cargo *cargo, FILE *fp, char *line, size_t *len) 
{
	int quantity = 0, from = 0, to = 0;
	while((getline(&line, len, fp) > 0)) {
		if((sscanf(line, "move %d from %d to %d", &quantity, &from, &to)) == 3) {
			move(cargo, quantity, from, to);
		}
	}
}

void output(Cargo *cargo, const char *title)
{
	printf("%s: ", title);
	for(int i = 0; i < STACKS; i ++) 
		printf("%c", cargo->stack[i].items[0]);
	printf("\n");
}

void run(FILE *fp, const char *title, const int limit) 
{
	rewind(fp);
	char *line = NULL;
	size_t len = 0;
	Cargo *cargo = malloc(sizeof(Cargo)); 
	cargo->limit = limit;
	parseInitialGrid(cargo, fp, line, &len);
	processInstructions(cargo, fp, line, &len);
	output(cargo, title);
	free(cargo);
}

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if(fp == NULL) {
		perror("Unable to open file input.txt");
		exit(1);
	}
	run(fp, "Part 1", 1);
	run(fp, "Part 2", 0);
	return 0;
}
