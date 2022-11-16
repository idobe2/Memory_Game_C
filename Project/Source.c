/*
Final Project - 30.05.21
Ido Ben Nun - 209202225
Noam Bar - 207994450
Bar Cohen - 316164938
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COL 6
#define MAX 20

struct card
{
	char* name;
	int state;
};

struct card** initialize(int* psize)
{
	struct card** board;
	char** words = NULL;
	int ran1, ran2;
	char word[MAX];
	time_t t;
	srand((unsigned)time(&t));
	board = (struct card**)malloc(*psize * sizeof(struct card*));
	if (!board)
	{
		printf("Error!\n");
		return 0;
	}
	for (int i = 0; i < *psize; i++)
	{
		board[i] = (struct card*)malloc(COL * sizeof(struct card));
		if (!board[i])
		{
			printf("Error!\n");
			return 0;
		}
	}
	words = (char**)malloc((*psize * 3) * sizeof(char*));
	if (!words)
	{
		printf("Error!");
		return 0;
	}
	for (int i = 0; i < (*psize * 3); i++)
	{
		printf("Enter word #%d\t", i + 1);
		scanf("%s", word);
		words[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
		if (!words[i])
		{
			printf("Error!");
			return 0;
		}
		strcpy(words[i], word);
		for (int j = 0; j < i; j++)
		{
			if (strcmp(words[j],words[i]) == 0)
			{
				printf("Same word detected!\n");
				i--;
				words[j] = (char*)malloc((strlen(word) + 1) * sizeof(char));
				if (!words[j])
				{
					printf("Error!");
					return 0;
				}
				strcpy(words[j], word);
			}
		}
	}
	for (int i = 0; i < (*psize * COL) / 2; i++)
	{
		ran1 = rand() % *psize;
		ran2 = rand() % COL;
		while (board[ran1][ran2].state == 1)
		{
			ran1 = rand() % *psize;
			ran2 = rand() % COL;
		}
		board[ran1][ran2].name = (char*)malloc((strlen(words[i]) + 1) * sizeof(char));
		if (!board[ran1][ran2].name)
		{
			printf("Error!\n");
			return NULL;
		}
		strcpy(board[ran1][ran2].name, words[i]);
		board[ran1][ran2].state = 1;
		ran1 = rand() % *psize;
		ran2 = rand() % COL;
		while (board[ran1][ran2].state == 1)
		{
			ran1 = rand() % *psize;
			ran2 = rand() % COL;
		}
		board[ran1][ran2].name = (char*)malloc((strlen(words[i]) + 1) * sizeof(char));
		if (!board[ran1][ran2].name)
		{
			printf("Error!\n");
			return NULL;
		}
		strcpy(board[ran1][ran2].name, words[i]);
		board[ran1][ran2].state = 1;
	}
	for (int i = 0; i < (*psize * 3); i++)
		free(words[i]);
	free(words);
	return board;
}

void print_board(int* psize, struct card** board)
{
	for (int i = 0; i < *psize; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j].state == 1)
				printf("-----\t");
			else
				printf("%s\t", board[i][j].name);
		}
		printf("\n");
	}
}

struct card** guess(int* psize, struct card** board)
{
	int index_i, index_j, index_i2, index_j2, counter = 0, res = 0;
	index_i = index_j = index_i2 = index_j2 = (-1);
	int size = *psize;
	print_board(&size, board);
	while (res == 0)
	{
		while (index_i < 0 || index_i >= *psize)
		{
			printf("Enter row number\n");
			scanf("%d", &index_i);
			index_i--;
			if (index_i < 0 || index_i >= *psize)
				printf("Invalit input, try again...\n");
		}
		while (index_j < 0 || index_j >= COL)
		{
			printf("Enter col number\n");
			scanf("%d", &index_j);
			index_j--;
			if (index_j < 0 || index_j >= COL)
				printf("Invalid input, try again...\n");
			if (board[index_i][index_j].state == 0)
			{
				printf("Card is already opened, try again...\n");
				index_j = (-1);
			}
		}
		board[index_i][index_j].state = 0;
		print_board(&size, board);
		while (index_i2 < 0 || index_i2 >= *psize)
		{
			printf("Enter row number\n");
			scanf("%d", &index_i2);
			index_i2--;
			if (index_i2 < 0 || index_i2 >= *psize)
				printf("Invalid input, try again...\n");
		}
		while (index_j2 < 0 || index_j2 >= COL)
		{
			printf("Enter col number\n");
			scanf("%d", &index_j2);
			index_j2--;
			if (index_j2 < 0 || index_j2 >= COL)
				printf("Invalid input, try again...\n");
			if (board[index_i2][index_j2].state == 0)
			{
				printf("Card is already opened, try again...\n");
				index_j2 = (-1);
			}
		}
		board[index_i2][index_j2].state = 0;
		print_board(&size, board);
		if (strcmp(board[index_i][index_j].name, board[index_i2][index_j2].name) != 0 || (index_i == index_i2 && index_j == index_j2))
		{
			board[index_i][index_j].state = 1;
			board[index_i2][index_j2].state = 1;
			printf("No match found!\n");
			print_board(&size, board);
		}
		else
			printf("Match found!\n");
		counter++;
		printf("Counter Guess: %d\n", counter);
		index_i = index_j = index_i2 = index_j2 = (-1);
		res = check(&size, board);
	}
}

int check(int* psize, struct card** board)
{
	for (int i = 0; i < *psize; i++)
	{
		for (int j = 0; j < COL; j++)
			if (board[i][j].state == 1)
				return 0;
	}
	printf("Winner Winner Chicken Dinner!!!\n");
	return 1;
}

int main()
{
	int size;
	struct card** board = NULL;
	printf("Enter number of rows\n");
	scanf("%d", &size);
	board = initialize(&size);
	guess(&size, board);
	for (int i = 0; i < size; i++)
		free(board[i]);
	free(board);
}