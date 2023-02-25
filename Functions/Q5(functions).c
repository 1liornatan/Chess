#ifndef Q5_FUNCTIONS_C
#define Q5_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q5.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	FILE* fp;
	chessPosCell* curr = NULL;
	BYTE* arr = NULL;
	int arr_size;
	short int sizeOfNodes = 0;
	if (pos_list == NULL)
	{
		fp = fopen(file_name, "wb");
		openFileCheckSuccess(fp);
		fclose(fp);
		return;
	}
	curr = pos_list->head;
	fp = fopen(file_name, "wb");
	openFileCheckSuccess(fp);
	fwrite(&sizeOfNodes, sizeof(short int), 1, fp); // Save place
	arr = createArrFromList(pos_list, &arr_size, &sizeOfNodes);
	threeBitsToFile(fp, arr, arr_size);
	fseek(fp, 0, SEEK_SET);
	fwrite(&sizeOfNodes, sizeof(short int), 1, fp);
	fseek(fp, 0, SEEK_END);
	fclose(fp);
	free(arr);
}

void threeBitsToFile(FILE* fp, BYTE* arr, int arr_size)
{
	BYTE mask0 = 0xE0; // 11100000
	BYTE mask1 = 0x1C; // 00011100
	BYTE mask2a = 0x03, mask2b = 0x80; // 00000011 10000000
	BYTE mask3 = 0x70; // 01110000
	BYTE mask4 = 0x0E; // 00001110
	BYTE mask5a = 0x01, mask5b = 0xC0; // 00000001 11000000
	BYTE mask6 = 0x38; // 00111000
	BYTE mask7 = 0x07; // 00000111
	BYTE byte = 0x00;
	BOOL flag = TRUE;
	int i, j = 0, size = arr_size;
	int numOfBytes = numOfBytesNeeded(arr_size);
	fillZeroes(fp, numOfBytes);
	for (i = 0; i < arr_size; i++)
	{
		flag = TRUE;
		if (j == 0)
		{
			byte = (arr[i] << 5) & mask0;
		}
		else if (j == 1)
		{
			byte = byte | ((arr[i] << 2) & mask1);
		}
		else if (j == 2)
		{
			byte = byte | ((arr[i] >> 1) & mask2a);
			fwrite(&byte, sizeof(BYTE), 1, fp);
			byte = (arr[i] << 7) & mask2b;
		}
		else if (j == 3)
		{
			byte = byte | ((arr[i] << 4) & mask3);
		}
		else if (j == 4)
		{
			byte = byte | ((arr[i] << 1) & mask4);
		}
		else if (j == 5)
		{
			byte = byte | ((arr[i] >> 2) & mask5a);
			fwrite(&byte, sizeof(BYTE), 1, fp);
			byte = (arr[i] << 6) & mask5b;
		}
		else if (j == 6)
		{
			byte = byte | ((arr[i] << 3) & mask6);
		}
		else if (j == 7)
		{
			byte = byte | (arr[i] & mask7);
			fwrite(&byte, sizeof(BYTE), 1, fp);
			j = -1;
			flag = FALSE;
		}
		j++;
	}
	if (flag)
		fwrite(&byte, sizeof(BYTE), 1, fp);
}

int numOfBytesNeeded(int arr_size)
{
	int num;
	if (arr_size % 8 == 0)
		num = (arr_size * 3) / 8;
	else
		num = (arr_size * 3) / 8 + 1;
	return num;
}

BYTE* createArrFromList(chessPosList* lst, int* size, short int* sizeOfNodes)
{
	BYTE* arr = NULL;
	chessPosCell* curr;
	int PhySize = 2, i = 0;
	short int numOfNodes = 0;
	curr = lst->head;
	arr = (BYTE*)malloc(PhySize * sizeof(BYTE));
	while (curr != NULL)
	{
		arr[i++] = conversion(curr->position[0]);
		arr[i++] = conversion(curr->position[1]);
		if (i >= PhySize)
		{
			PhySize *= 2;
			arr = (BYTE*)realloc(arr, PhySize * sizeof(BYTE));
		}
		numOfNodes++;
		curr = curr->next;
	}
	*sizeOfNodes = numOfNodes;
	*size = i;
	arr = (BYTE*)realloc(arr, (*size) * sizeof(BYTE));
	return arr;
}

void fillZeroes(FILE* fp, int numOfBytes)
{
	long int saver;
	BYTE zero = 0x00;
	saver = ftell(fp);
	fwrite(&zero, sizeof(BYTE), numOfBytes, fp);
	fseek(fp, saver, SEEK_SET);
}

BYTE conversion(char ch)
{
	BYTE val = '-1';
	switch (ch)
	{
	case 'A':
	case '1':
		val = 0x00; // 00000000
		break;
	case 'B':
	case '2':
		val = 0x01; // 00000001
		break;
	case 'C':
	case '3':
		val = 0x02; // 00000010
		break;
	case 'D':
	case '4':
		val = 0x03; // 00000011
		break;
	case 'E':
	case '5':
		val = 0x04; // 00000100
		break;
	case 'F':
	case '6':
		val = 0x05; // 00000101
		break;
	case 'G':
	case '7':
		val = 0x06; // 00000110
		break;
	case 'H':
	case '8':
		val = 0x07; // 00000111
		break;
	}
	return val;
}

void openFileCheckSuccess(FILE* fp)
{
	if (fp == NULL)
	{
		printf("Error while creating a file. Exiting...");
		exit(1);
	}
	else
		return;
}
#endif