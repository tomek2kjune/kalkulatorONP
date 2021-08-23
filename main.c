#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <locale.h>

typedef struct
{
	double ReZ;
	double ImZ;
}complex;

typedef struct
{
	complex data;
	struct element* previous;
}element;

//add element to stack
void push(element** stack, complex new)
{
	element* compNum = malloc(sizeof(element));
	compNum->data = new;
	compNum->previous = *stack;
	*stack = compNum;
}

//get element from stack
complex pop(element** stack)
{
	element* top = *stack;
	complex compValue = top->data;
	*stack = top->previous;
	free(top);
	return compValue;
}

//add elements
complex add(complex c1, complex c2) 
{
	complex newcomplex;
	newcomplex.ReZ = c1.ReZ + c2.ReZ;
	newcomplex.ImZ = c1.ImZ + c2.ImZ;

	return newcomplex;
}

//subtract elements
complex subtract(complex c1, complex c2) 
{
	complex newcomplex;
	newcomplex.ReZ = c1.ReZ - c2.ReZ;
	newcomplex.ImZ = c1.ImZ - c2.ImZ;

	return newcomplex;
}

//divide elements
complex divide(complex c1, complex c2) 
{
	complex newcomplex;
	newcomplex.ReZ = c1.ReZ / c2.ReZ;
	newcomplex.ImZ = c1.ImZ / c2.ImZ;

	return newcomplex;
}

//multiply elements
complex multiply(complex c1, complex c2) 
{
	complex newcomplex;
	newcomplex.ReZ = c1.ReZ * c2.ReZ;
	newcomplex.ImZ = c1.ImZ * c2.ImZ;

	return newcomplex;
}

//list elements from stack
void show(element** stack, int stackSize)
{
	element* comp = malloc(sizeof(stack));
	comp = *stack;
	printf("Wprowadzone liczby:\n");
	for (int i = 0; i < stackSize; i++)
	{
		printf("%lf %lfi\n", comp->data.ReZ, comp->data.ImZ);
		comp = comp->previous;
	}
}

int main()
{
	setlocale(LC_ALL, "Polish");

	element* top = NULL;
	int stackSize = 0;
	char* input;

	while (1) 
	{
		printf("++++++++++++++++++++++++++++++++++++\n");
		printf("KALKULATOR ONP DLA LICZB ZESPOLONYCH\n");
		printf("++++++++++++++++++++++++++++++++++++\n\n");
		printf("Wprowadź liczbę lub operator + - / * w formacie ONP:\n");
		char* input;
		input = NULL;
		complex newcomp;
		gets(&input);
		
		if (input == '+') 
		{
			if (stackSize <= 1)
			{
				printf("Zbyt mało danych do wykonania operacji!");
				Sleep(500);
				continue;
			}
			else
			{
				push(&top, add(pop(&top), pop(&top)));
				stackSize--;
			}
		}
		else if (input == '-') {
			if (stackSize <= 1)
			{
				printf("Zbyt mało danych do wykonania operacji :/");
				Sleep(500);
				continue;
			}
			else
			{
				push(&top, subtract(pop(&top), pop(&top)));
				stackSize--;
			}
		}
		else if (input == '/') {
			if (stackSize <= 1)
			{
				printf("Zbyt mało danych do wykonania operacji :/");
				Sleep(500);
				continue;
			}
			else
			{
				push(&top, divide(pop(&top), pop(&top)));
				stackSize--;
			}
		}
		else if (input == '*') {
			if (stackSize <= 1)
			{
				printf("Zbyt mało danych do wykonania operacji :/");
				Sleep(500);
				continue;
			}
			else
			{
				push(&top, multiply(pop(&top), pop(&top)));
				stackSize--;
			}
		}
		else 
		{
			sscanf(&input, "%lf %lf", &newcomp.ReZ, &newcomp.ImZ);
			printf("%lf %lfi\n", newcomp.ReZ, newcomp.ImZ);
			push(&top, newcomp);
			stackSize++;
		}
		show(&top, stackSize);
		printf("Aby kontynuować wciśnij [Enter]");
		getchar();
		while (getchar == "\n");
		system("CLS");
	}
	return 0;
}