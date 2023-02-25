#ifndef Q2_FUNCTIONS_C
#define Q2_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q2.h"

void falseAll(BOOL arr[][SIZE_BOARD])
{
	int i, j;
	for (i = 0; i < SIZE_BOARD; i++)
	{
		for (j = 0; j < SIZE_BOARD; j++)
		{
			arr[i][j] = FALSE;
		}
	}
}

void display(chessPosList* lst)
{
	deleteDuplicates(lst);
	BuildBoard(lst);
}

void BuildBoard(chessPosList* lst)
{
	int board[SIZE_BOARD][SIZE_BOARD];
	chessPosCell* curr = NULL;
	int i, j;
	int row_index, col_index, counter = 1;
	if (lst != NULL)
		curr = lst->head;
	for (i = 0; i < SIZE_BOARD; i++) // Filling the board
	{
		for (j = 0; j < SIZE_BOARD; j++)
		{
			board[i][j] = 0;
		}
	}
	while (curr != NULL) // Serial number of each node in list
	{
		row_index = charLetterToIndexArr(curr->position[0]);
		col_index = charNumberToIndexArr(curr->position[1]);
		board[row_index][col_index] = counter;
		counter++;
		curr = curr->next;
	}
	printBoard(board);
}

void printBoard(int board[][SIZE_BOARD])
{
	int i, j;
	char ch = 'A';
	for (i = 0; i <= SIZE_BOARD; i++)
	{
		for (j = 0; j <= SIZE_BOARD; j++)
		{
			if (i == 0 && j == 0) // Meaningless square
				printf(" ");
			else if (i == 0) // Numbers
				printf(YELLOW "%4d" RESET, j);
			else if (j == 0) // Letters
			{
				printf(YELLOW "%c" RESET, ch);
				ch++;
			}
			else
			{
				if (j == SIZE_BOARD)
				{
					if (board[i - 1][j - 1] == 0)
						printf("|   |");
					else
						printf("|%3d|", board[i - 1][j - 1]);
				}
				else
				{
					if (board[i - 1][j - 1] == 0)
						printf("|   ");
					else
						printf("|%3d", board[i - 1][j - 1]);
				}
			}
		}
		printBorders();
	}
}

void printBorders()
{
	printf("\n");
	for (int k = 0; k < (SIZE_BOARD * 4 + 2); k++)
		printf("-");
	printf("\n");
}

void deleteDuplicates(chessPosList* lst)
{
	if (lst == NULL || lst->head == NULL || lst->head->next == NULL)
		return;
	chessPosCell* currRunner, * currSaver;
	BOOL presence[SIZE_BOARD][SIZE_BOARD];
	int row_index, col_index;
	currSaver = lst->head;
	currRunner = lst->head->next;
	falseAll(presence);
	row_index = charLetterToIndexArr(currSaver->position[0]);
	col_index = charNumberToIndexArr(currSaver->position[1]);
	presence[row_index][col_index] = TRUE;
	while (currRunner != NULL)
	{
		row_index = charLetterToIndexArr(currRunner->position[0]);
		col_index = charNumberToIndexArr(currRunner->position[1]);
		if (presence[row_index][col_index] == FALSE)
		{
			presence[row_index][col_index] = TRUE;
			currSaver = currRunner;
			currRunner = currRunner->next;
		}
		else
		{
			deleteNode(lst, currSaver, currRunner);
			currRunner = currSaver->next;
		}
	}
	chessPosCell* curr = lst->head;
	printf("The list without duplicated nodes:\n");
	while (curr != NULL)
	{
		printf("%c%c ", curr->position[0], curr->position[1]);
		curr = curr->next;
	}
	printf("\n\n");
}

void deleteNode(chessPosList* lst, chessPosCell* currPrev, chessPosCell* currDelete)
{
	if (currDelete->next == NULL) // currDelete is the last node in list
	{
		lst->tail = currPrev;
		currPrev->next = NULL;
	}
	else
	{
		currPrev->next = currDelete->next;
		currDelete->next = NULL;
	}
	free(currDelete);
}

void freeList(chessPosList* lst)
{
	chessPosCell* curr;
	chessPosCell* currSaver;
	curr = lst->head;
	while (curr != NULL)
	{
		currSaver = curr;
		curr = curr->next;
		free(currSaver);
	}
}
#endif