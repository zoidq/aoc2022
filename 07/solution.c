#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES			32
#define MAX_FILE_LENGTH		32
#define PART1_SUM			100000
#define TOTAL_SPACE			70000000
#define TOTAL_REQUIRED		30000000

typedef struct File {
	size_t size;
	char name[MAX_FILE_LENGTH];
} File;

typedef struct Dir {
	char path[MAX_FILE_LENGTH];
	struct Dir *parent;
	struct Dir *dirs[MAX_FILES];
	struct File *files[MAX_FILES];
} Dir;

Dir *addDir(Dir *cwd, const char *path) 
{
	Dir *dir = malloc(sizeof(Dir));
	dir->parent = cwd;
	strcpy(dir->path, path);

	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->dirs[i] == NULL) {
			cwd->dirs[i] = dir;
			break;
		}
	}

	return dir;
}

void addFile(Dir *cwd, const char *name, const size_t size) {
	File *file = malloc(sizeof(File));
	file->size = size;
	strcpy(file->name, name);
	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->files[i] == NULL) {
			cwd->files[i] = file;
			break;
		}
	}
}

int sumDir(Dir *cwd) 
{
	int sum = 0;
	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->files[i] != NULL) {
			sum += cwd->files[i]->size;
		}
	}

	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->dirs[i] != NULL) {
			sum += sumDir(cwd->dirs[i]);
		}
	}

	return sum;
}

int part1(Dir *cwd, int sum)
{
	int local = 0, limit = 0;
	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->dirs[i] != NULL) {
			local = sumDir(cwd->dirs[i]);
			if(local <= PART1_SUM) { limit = local; } else { limit = 0; }
			sum += part1(cwd->dirs[i], limit);
		}
	}

	return sum;
}

/*
int part1(int sum) 
{
	if(sum <= PART1_SUM) 
		return sum;

	return 0;
}
*/


int part2(Dir *cwd, int smallest, int required) 
{
	int local = 0;
	for(int i = 0; i < MAX_FILES; i ++) {
		if(cwd->dirs[i] != NULL) {
			local = sumDir(cwd->dirs[i]);

			if(local >= required && local < smallest)  
				smallest = local;

			smallest = part2(cwd->dirs[i], smallest, required);
		}
	}

	return smallest;
}

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if(fp == NULL) {
		perror("Unable to open input.txt");
		exit(1);
	}

	char arg[3][MAX_FILE_LENGTH];
	char *line = NULL;
	size_t len = 0;
	int i;

	Dir *dir = malloc(sizeof(Dir));
	Dir *root = dir;
	strcpy(dir->path, "/");

	while((getline(&line, &len, fp)) > 0) {
		sscanf(line, "%s %s %s", arg[0], arg[1], arg[2]);

		// Change directory
		if(strcmp(arg[0], "$") == 0 && strcmp(arg[1], "cd") == 0) {

			// Change to parent directory
			if(strcmp(arg[2], "..") == 0) {
				if(dir->parent != NULL) {
					dir = dir->parent;
				}
			}

			// Change to named directory
			else {
				for(i = 0; i < MAX_FILES; i ++) {
					if(dir->dirs[i] != NULL) {
						if(strcmp(dir->dirs[i]->path, arg[2]) == 0) {
							dir = dir->dirs[i];
							break;
						}
					}
				}
			}
			continue;
		}

		// List directory
		if(strcmp(arg[0], "$") == 0 && strcmp(arg[1], "ls") == 0) {
			continue;
		}

		// Add directory
		if(strcmp(arg[0], "dir") == 0) {
			addDir(dir, arg[1]);
		} 
	
		// Add file
		else {
			addFile(dir, arg[1], atoi(arg[0]));
		}

	}

	int sum1 = part1(root, 0);
	printf("\nPart 1 sum: %d\n", sum1);

	int required = TOTAL_REQUIRED - (TOTAL_SPACE - sumDir(root));
	int sum2 = part2(root, INT32_MAX, required);
	printf("\nPart 2 sum: %d\n", sum2);

	return 0;
}
