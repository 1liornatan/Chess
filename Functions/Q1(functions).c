#ifndef Q1_FUNCTIONS_C
#define Q1_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q1.h"

chessPosArray*** validKnightMoves() {
	chessPosArray*** boardArr = (chessPosArray***)malloc(sizeof(chessPosArray**) * SIZE_BOARD);
	for (int i = 0; i < SIZE_BOARD; i++)
		boardArr[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * SIZE_BOARD);
	setKnightMoves(boardArr);

	return boardArr;
}

void setKnightMoves(chessPosArray*** boardArr) {
	int i, j;

	for (i = 1; i <= SIZE_BOARD; i++) {
		for (j = 1; j <= SIZE_BOARD; j++) {
			boardArr[i - 1][j - 1] = getPositionsArr(i, j);
		}
	}

}

chessPosArray* getPositionsArr(int i, int j) {

	chessPosArray* posArr = (chessPosArray*)malloc(sizeof(chessPosArray));
	posArr->positions = NULL;
	posArr->size = 0;

	if (isValidPos(i + 2, j + 1)) {
		addPosToArr(posArr, i + 2, j + 1);
	}

	if (isValidPos(i + 2, j - 1)) {
		addPosToArr(posArr, i + 2, j - 1);
	}

	if (isValidPos(i - 2, j + 1)) {
		addPosToArr(posArr, i - 2, j + 1);
	}

	if (isValidPos(i - 2, j - 1)) {
		addPosToArr(posArr, i - 2, j - 1);
	}

	if (isValidPos(i + 1, j + 2)) {
		addPosToArr(posArr, i + 1, j + 2);
	}

	if (isValidPos(i + 1, j - 2)) {
		addPosToArr(posArr, i + 1, j - 2);
	}

	if (isValidPos(i - 1, j + 2)) {
		addPosToArr(posArr, i - 1, j + 2);
	}

	if (isValidPos(i - 1, j - 2)) {
		addPosToArr(posArr, i - 1, j - 2);
	}

	return posArr;
}

BOOL isValidPos(int i, int j) {
	if ((i >= 1) && (i <= SIZE_BOARD) && (j >= 1) && (j <= SIZE_BOARD))
		return TRUE;
	else
		return FALSE;
}

void addPosToArr(chessPosArray* posArr, int i, int j) {
	if (posArr->positions == NULL) {
		posArr->positions = (chessPos*)malloc(sizeof(chessPos));
		posArr->size = 1;
	}
	else {
		posArr->positions = (chessPos*)realloc(posArr->positions, (posArr->size + 1) * sizeof(chessPos));
		posArr->size++;
	}

	if (posArr->positions != NULL) {
		posArr->positions[posArr->size - 1][0] = (i + 'A' - 1);
		posArr->positions[posArr->size - 1][1] = (j + '0');
	}
	else {
		printf("Memory Allocation Failure!\n");
		exit(1);
	}
}
#endif