#ifndef Q6_FUNCTIONS_C
#define Q6_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q6.h"

char conversionTochar(BYTE byte, int numParity)
{
	char val = '-1';
	switch (byte)
	{
	case 0x00:
		if (numParity % 2 == 0)
			val = 'A';
		else
			val = '1';
		break;
	case 0x01:
		if (numParity % 2 == 0)
			val = 'B';
		else
			val = '2';
		break;
	case 0x02:
		if (numParity % 2 == 0)
			val = 'C';
		else
			val = '3';
		break;
	case 0x03:
		if (numParity % 2 == 0)
			val = 'D';
		else
			val = '4';
		break;
	case 0x04:
		if (numParity % 2 == 0)
			val = 'E';
		else
			val = '5';
		break;
	case 0x05:
		if (numParity % 2 == 0)
			val = 'F';
		else
			val = '6';
		break;
	case 0x06:
		if (numParity % 2 == 0)
			val = 'G';
		else
			val = '7';
		break;
	case 0x07:
		if (numParity % 2 == 0)
			val = 'H';
		else
			val = '8';
		break;
	}
	return val;
}

int nodesToBits(short int numOfNodes)
{
	int num;
	numOfNodes *= 2;
	num = (int)(numOfNodes * 3);
	return num;
}

chessPosList getListFromFile(FILE* fp)
{
	chessPosList res;
	char dump[2];
	BYTE mask1 = 0x03; // 00000011
	BYTE mask2 = 0x01; // 00000001
	BYTE mask3 = 0x07; // 00000111
	BYTE mask4 = 0x06; // 00000110
	BYTE mask5 = 0x04; // 00000100
	BYTE byte, byteHelper;
	short int num_of_nodes;
	int i = 0, j = 0, numOfBits;
	makeEmptyList(&res);
	fread(&num_of_nodes, sizeof(short int), 1, fp);
	numOfBits = nodesToBits(num_of_nodes);
	while (i < numOfBits)
	{
		if (j == 0)
		{
			fread(&byte, sizeof(byte), 1, fp);
			dump[0] = conversionTochar(((byte >> 5) & mask3), 0);
			dump[1] = conversionTochar(((byte >> 2) & mask3), 1);
			insertDataToEndList(&res, dump[0], dump[1]);
			i += 6;
		}
		else if (j == 2)
		{
			fread(&byteHelper, sizeof(BYTE), 1, fp);
			dump[0] = conversionTochar((((byte << 1) & mask4) | ((byteHelper >> 7) & mask2)), 0);
			byte = byteHelper;
			dump[1] = conversionTochar(((byte >> 4) & mask3), 1);
			insertDataToEndList(&res, dump[0], dump[1]);
			i += 6;
		}
		else if (j == 4)
		{
			dump[0] = conversionTochar(((byte >> 1) & mask3), 0);
			fread(&byteHelper, sizeof(BYTE), 1, fp);
			dump[1] = conversionTochar((((byte << 2) & mask5) | ((byteHelper >> 6) & mask1)), 1);
			byte = byteHelper;
			insertDataToEndList(&res, dump[0], dump[1]);
			i += 6;
		}
		else if (j == 6)
		{
			dump[0] = conversionTochar(((byte >> 3) & mask3), 0);
			dump[1] = conversionTochar((byte & mask3), 1);
			insertDataToEndList(&res, dump[0], dump[1]);
			j = -2;
			i += 6;
		}
		j += 2;
	}
	return res;
}

void insertDataToEndList(chessPosList* lst, char letter, char num)
{
	chessPosCell* node;
	node = createNewListNode(letter, num, NULL);
	insertNodeToEndList(lst, node);
}

chessPosCell* createNewListNode(char letter, char num, chessPosCell* next)
{
	chessPosCell* node;
	node = (chessPosCell*)malloc(sizeof(chessPosCell));
	if (node == NULL)
		exit(1);
	else
	{
		node->position[0] = letter;
		node->position[1] = num;
		node->next = next;
	}
	return node;
}

void insertNodeToEndList(chessPosList* lst, chessPosCell* node)
{
	if (IsEmptyList(lst))
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	node->next = NULL;
}

BOOL IsEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp;
	fp = fopen(file_name, "rb");
	if (fp == NULL)
		return FILE_NOT_FOUND;
	chessPosList lst = getListFromFile(fp);
	fclose(fp);
	if (lst.head == NULL)
	{
		display(&lst);
		return NO_COVER_PATH_FOUND;
	}
	chessPosArray*** knightMovesArr = validKnightMoves();
	if (!isValidPath(knightMovesArr, &lst))
	{
		printList(&lst);
		freeList(&lst);
		freeKnightMovesArr(knightMovesArr);
		return NOT_VALID_PATH;
	}
	freeKnightMovesArr(knightMovesArr);
	display(&lst);
	if (isPathCoversAllBoard(&lst))
	{
		freeList(&lst);
		return PATH_COVERS_ALL_BOARD;
	}
	freeList(&lst);
	return NO_COVER_PATH_FOUND;
}

BOOL isValidPath(chessPosArray*** knightMovesArr, chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	chessPosCell* currNext = curr->next;
	if (currNext == NULL)
		return TRUE;
	while (currNext != NULL)
	{
		if (!isPositionInKnightMovesArr(knightMovesArr, curr, currNext))
			return FALSE;
		curr = currNext;
		currNext = currNext->next;
	}
	return TRUE;
}

BOOL isPositionInKnightMovesArr(chessPosArray*** knightMovesArr, chessPosCell* curr, chessPosCell* currNext)
{
	int i;
	int row_index = charLetterToIndexArr(curr->position[0]);
	int col_index = charNumberToIndexArr(curr->position[1]);
	for (i = 0; i < knightMovesArr[row_index][col_index]->size; i++)
	{
		if (knightMovesArr[row_index][col_index]->positions[i][0] == currNext->position[0]
			&& knightMovesArr[row_index][col_index]->positions[i][1] == currNext->position[1])
			return TRUE;
	}
	return FALSE;
}

int charLetterToIndexArr(char ch)
{
	int val = -1;
	switch (ch)
	{
	case 'A':
		val = 0;
		break;
	case 'B':
		val = 1;
		break;
	case 'C':
		val = 2;
		break;
	case 'D':
		val = 3;
		break;
	case 'E':
		val = 4;
		break;
	case 'F':
		val = 5;
		break;
	case 'G':
		val = 6;
		break;
	case 'H':
		val = 7;
		break;
	}
	return val;
}

int charNumberToIndexArr(char num)
{
	int val;
	val = (num - '0') - 1;
	return val;
}

void freeKnightMovesArr(chessPosArray*** arr)
{
	int i, j;
	for (i = 0; i < SIZE_BOARD; i++)
	{
		for (j = 0; j < SIZE_BOARD; j++)
		{
			free(arr[i][j]->positions);
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);
}

BOOL isPathCoversAllBoard(chessPosList* lst)
{
	if (IsEmptyList(lst))
		return FALSE;
	chessPosCell* curr = lst->head;
	int counter = 0;
	while (curr != NULL)
	{
		counter++;
		curr = curr->next;
	}
	if (counter == SIZE_BOARD * SIZE_BOARD)
		return TRUE;
	else
		return FALSE;
}

void printPathState(int path_state)
{
	if (path_state == FILE_NOT_FOUND)
		printf(PINK "FILE_NOT_FOUND\n\n" RESET);
	if (path_state == NOT_VALID_PATH)
		printf(PINK "NOT_VALID_PATH\n\n" RESET);
	if (path_state == NO_COVER_PATH_FOUND)
		printf(PINK "\n\NO_COVER_PATH_FOUND\n\n" RESET);
	if (path_state == PATH_COVERS_ALL_BOARD)
		printf(PINK "PATH_COVERS_ALL_BOARD\n\n" RESET);
}
//check
void printList(chessPosList* lst)
{
	chessPosCell* curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("%c", curr->position[0]);
		printf("%c ", curr->position[1]);
		curr = curr->next;
	}
	printf("\n");
}
#endif