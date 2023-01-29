#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))
#define hideCursor() printf("\e[?25l")
#define showCursor() printf("\e[?25h")
#define clearColor() printf("\033[0m")

#define SIZE_WIDTH 80
#define SIZE_HEIGHT 80

int update();
int draw();

int matrix[SIZE_HEIGHT][SIZE_WIDTH] = {{0}};
int stateMatrix[SIZE_HEIGHT][SIZE_WIDTH] = {{0}};

int countNeighbors(int x, int y) {
	int nei = 0;
	if (x > 0 && matrix[y][x - 1]) nei++;
	if (x < SIZE_WIDTH && matrix[y][x + 1]) nei++;
	if (y > 0 && matrix[y - 1][x]) nei++;
	if (y < SIZE_HEIGHT && matrix[y + 1][x]) nei++;
	if (x > 0 && y > 0 && matrix[y - 1][x - 1]) nei++;
	if (x > 0 && y < SIZE_HEIGHT && matrix[y + 1][x - 1]) nei++;
	if (x < SIZE_WIDTH && y > 0 && matrix[y - 1][x + 1]) nei++;
	if (x < SIZE_WIDTH && y < SIZE_HEIGHT && matrix[y + 1][x + 1]) nei++;
	return nei;
}
int update() {
	for (int y = 0; y < SIZE_HEIGHT; y++) {
		for (int x = 0; x < SIZE_WIDTH; x++) {
			int nei = countNeighbors(x, y);
			if (nei == 3 && !matrix[y][x])
				stateMatrix[y][x] = 1;
			else
			if ((nei == 2 || nei == 3) && matrix[y][x])
				stateMatrix[y][x] = 1;
			else
				stateMatrix[y][x] = 0;
			//stateMatrix[y][x] = 1;	
		}
	}
	return draw();
}
int draw() {
 	for (int y = 0; y < SIZE_HEIGHT; y++) {
 		for (int x = 0; x < SIZE_WIDTH; x++) {
			gotoxy(x * 2, y);
			matrix[y][x] = stateMatrix[y][x];
 			if (matrix[y][x])
				printf("[]");
			else
				printf("  ");
		}
	}
	return 1;
}
int main(void) {
	srand(time(NULL));
	int timer = 0;
 	for (int y = 0; y < SIZE_HEIGHT; y++) {
 		for (int x = 0; x < SIZE_WIDTH; x++) {
			matrix[y][x] = rand() % 2;
		}
	}	
	int tick = 0;
	hideCursor();
	int updated = 1;
	int drawn = 0;
 	while(1) {
		timer += 1;
 		if (timer >= 100000000 && updated) {
			timer = 0;
			updated = update();
			tick++;
			gotoxy(0, 0);
			printf("%d", tick);
		}
	}	
	return 0;
}
