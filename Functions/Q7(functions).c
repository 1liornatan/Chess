#ifndef Q7_FUNCTIONS_C
#define Q7_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q7.h"
int menu()
{
	int choice;
	BOOL isValidInput = FALSE;
	while (!isValidInput)
	{
		printf("1. Enter a knight's starting position.\n");
		printf("2. Create all possible knight paths.\n");
		printf("3. Find a knight path covering all board.\n");
		printf("4. Save knight path covering all board to file.\n");
		printf("5. Load and display path from file.\n");
		printf("6. Exit.\n\n");
		printf("Your choice is: ");
		scanf("%d", &choice);
		isValidInput = isValidChoice(choice);
	}
	return choice;
}

BOOL isValidChoice(int choice)
{
	if (choice >= 1 && choice <= 6)
		return TRUE;
	else
	{
		system("cls");
		printf(RED "Invalid input. Try again.\n\n" RESET);
		return FALSE;
	}
}

void getKnightStartingPosition(chessPos position)
{
	printf("\nEnter a knight starting position: ");
	scanf("\n%c%c", &position[0], &position[1]);
	while (!isValidKnightPosition(position))
	{
		printf(RED "\nInvalid input." RESET);
		printf("\nEnter a knight starting position: ");
		scanf("\n%c%c", &position[0], &position[1]);
		printf("\n");
	}
}

BOOL isValidKnightPosition(chessPos position)
{
	if (position[0] >= 'A' && position[0] <= 'A' + (SIZE_BOARD - 1) && position[1] >= '1' && position[1] <= '1' + (SIZE_BOARD - 1))
		return TRUE;
	else
		return FALSE;
}

char* getFileName()
{
	char* name = NULL;
	int phySize = 1, i = 0;
	char ch;
	BOOL endOfInput = FALSE, firstEnter = FALSE;
	name = (char*)malloc(phySize * sizeof(char));
	printf("Enter the file name (.bin): ");
	while (!endOfInput)
	{
		ch = getchar();
		if (ch == 10 && firstEnter == TRUE)
			break;
		firstEnter = TRUE;
		if (ch != 10)
		{
			name[i] = ch;
			i++;
			if (phySize <= i)
			{
				phySize *= 2;
				name = (char*)realloc(name, phySize * sizeof(char));
			}
		}
	}
	name = (char*)realloc(name, (i + 1) * sizeof(char));
	name[i] = '\0';
	return name;
}

void endPrint()
{
	printf(GREEN "****       *     *      ******\n");
	printf("*   *      *     *      *\n");
	printf("*    *     *     *      *\n");
	printf("*   *      *     *      *\n");
	printf("*****        ***        ******\n");
	printf("*   *         *         *\n");
	printf("*    *        *         *\n");
	printf("*   *         *         *\n");
	printf("****          *         ******\n" RESET);
}
#endif