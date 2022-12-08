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

void addToStack(Cargo *cargo, const int index, const char item)
{
	Stack *stack = &cargo->stack[index];
	strncat(stack->items, &item, 1);
}

void swap(char *src, char *dst, int quantity) 
{
	/*
	char str1[MAX_SIZE];
	sprintf(str1, "%c%s", src[0], dst);
	strcpy(dst, str1);
	memmove(src, src+1,strlen(src)-1);
	src[strlen(src)-1] = '\0';
	*/

	char str1[MAX_SIZE] = "";
	strncpy(str1, src, quantity);
	strcat(str1, dst);
	strcpy(dst, str1);
	memmove(src, src+quantity,strlen(src)-1);
	src[strlen(src)-1] = '\0';
}

void move(Cargo *cargo, const int quantity, const int from, const int to) 
{
	Stack *src = &cargo->stack[from-1];
	Stack *dst = &cargo->stack[to-1];
	int crates = 1;
	

	//printf("%s\n%s\n\n", src->items, dst->items);
	for(int i = 0; i < quantity; i += crates) {
		swap(src->items, dst->items, crates);
	}
	//printf("%s\n%s\n\n", src->items, dst->items);
}

void parseInitialGrid(Cargo *cargo, FILE *fp, char *line, size_t *len) 
{
	char item;
	int c = 0, i, index;
	while((getline(&line, len, fp) > 0) && c++ <= GRID_HEIGHT) {
		index = 0;
		for(i = 1; i < GRID_WIDTH; i += 4) {
			item = line[i];
			if(item != ' ') {
				addToStack(cargo,index, item);
			}
			index ++;
		}
	}
}

void parseInstructions(Cargo *cargo, FILE *fp, char *line, size_t *len) 
{
	int quantity = 0, from = 0, to = 0, c = 0;
	while((getline(&line, len, fp) > 0)) {
		if(c++ == 0) 
			continue;

		if((sscanf(line, "move %d from %d to %d", &quantity, &from, &to)) == 3) {
			move(cargo, quantity, from, to);
		}
	}
}

void part1(FILE *fp, char *line, size_t *len)
{
	Cargo *cargo = malloc(sizeof(Cargo));
	cargo->limit = 1;
	parseInitialGrid(cargo, fp, line, len);
	parseInstructions(cargo, fp, line, len);

	for(int i = 0; i < STACKS; i ++) {
		printf("%c", cargo->stack[i].items[0]);
	}
	printf("\n");
	free(cargo);
}

void part2(FILE *fp, char *line, size_t *len)
{
	Cargo *cargo = malloc(sizeof(Cargo));
	cargo->limit = 0;
	parseInitialGrid(cargo, fp, line, len);
	parseInstructions(cargo, fp, line, len);

	for(int i = 0; i < STACKS; i ++) {
		printf("%c", cargo->stack[i].items[0]);
	}
	printf("\n");
	free(cargo);
}

int main()
{
	// MQSHJMWNH is correct
	FILE *fp = fopen("input.txt", "r");
	if(fp == NULL) {
		perror("Unable to open file input.txt");
		exit(1);
	}
	char *line = NULL;
	size_t len;

	part1(fp, line, &len);
	part2(fp, line, &len);

	return 0;
}
