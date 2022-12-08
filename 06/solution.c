#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 4096
#define MARKER_SIZE 4
#define MESSAGE_SIZE 14

int check(char *marker) 
{
	for(int i = 0; i < strlen(marker); i ++) {
		for(int j = 0; j < strlen(marker); j ++) {
			if(i == j)
				continue;

			else if(marker[i] == marker[j])
				return 1;
		}
	}
	return 0;
}

int find(const char *data, const int len)
{
	char marker[len+1];
	int dataLen = strlen(data);
	for(int i = 0; i < dataLen; i ++) {
		if((i+(len+1)) > dataLen) return -1;	
		memcpy(marker, data+i, len);
		marker[len] = '\0';

		if((check(marker)) == 0) {
			return i+len;
		};
	}
	return 0;
}

void part1(char *data)
{
	printf("Start-of-packet marker: %d\n", find(data, MARKER_SIZE));
}

void part2(char *data)
{
	printf("Start-of-message marker: %d\n", find(data, MESSAGE_SIZE));
}

int main() 
{
	FILE *fp = fopen("input.txt", "r");
	if(fp == NULL) {
		perror("Unable to open input.txt");
		exit(1);
	}
	char *data = malloc(INPUT_SIZE);
	fread(data, 1, INPUT_SIZE, fp);
	part1(data);
	part2(data);
	free(data);
	return 0;
}
