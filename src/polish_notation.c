#include <stdlib.h>
#include <stdio.h>

typedef	int	bool;
#define	TRUE	1
#define	FALSE	0

float *STACK;
float TOP = 0;
int carret = 0;
int SIZE = 64;
void push(float el);
void pop();
int operation = -1;

int main(int argc, char** args) {
	STACK = malloc(SIZE * sizeof(float));
	for (int i = 0; i < SIZE; i++)
	{
		STACK[i] = 0;
	}
	float result = 0;
	for (int i = 1; i < argc; i ++) 
	{
		switch (args[i][0])
		{
			case '+': operation = 0;
				break;
			case '-': operation = 1;
				break;
			case '*': operation = 2;
				break;
			case '/': operation = 3;
				break;
			default:
				operation = -1;
		}
		if (operation == -1)
		{
			push((float)atof(args[i]));
		}
		else
		{
			float current = TOP;
			pop();
			switch (operation) {
				case	0: current += TOP; break;
				case	1: current -= TOP; break;
				case	2: current *= TOP; break;
				case	3: current /= TOP; break;
			}
			pop();
			
			push(current);
			result = current;
		}
	}
	printf("%f", result);
	free(STACK);
	return 0;
}

void push(float el) {
	STACK[carret] = el;
	TOP = el;
	carret++;
}

void pop() {
	carret--;
	TOP = STACK[carret - 1];
}

