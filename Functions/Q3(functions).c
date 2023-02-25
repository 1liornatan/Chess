#ifndef Q3_FUNCTIONS_C
#define Q3_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q3.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {
	BOOL usedPaths[SIZE_BOARD][SIZE_BOARD];
	int i, j;
	pathTree pathTr;
	treeNode* pathTn;
	chessPosArray*** boardArr;

	for (i = 0; i < SIZE_BOARD; i++)
		for (j = 0; j < SIZE_BOARD; j++)
			usedPaths[i][j] = FALSE;

	pathTn = makeTreeNode(*startingPosition);
	pathTr.root = pathTn;

	i = boardCharToIndex((*startingPosition)[0]);
	j = boardCharToIndex((*startingPosition)[1]);
	usedPaths[i][j] = TRUE;
	boardArr = validKnightMoves();

	makePathTree(pathTn, usedPaths, boardArr);
	freeChessPosArray(boardArr);
	return pathTr;
}

int boardCharToIndex(char ch) {
	if (isDigit(ch))
		return ch - '1';
	else
		return ch - 'A';
}

BOOL isDigit(char ch) {
	return (ch >= '0' && ch <= '9');
}

void makePathTree(treeNode* tn, BOOL usedPaths[SIZE_BOARD][SIZE_BOARD], chessPosArray*** boardArr) {

	int parentRow, parentCol, i, childRow, childCol, arrSize;
	chessPosArray* positionsArr;
	treeNodeListCell* curListCell = NULL;

	parentRow = boardCharToIndex(tn->position[0]);
	parentCol = boardCharToIndex(tn->position[1]);

	positionsArr = boardArr[parentRow][parentCol];

	arrSize = (positionsArr->size);

	for (i = 0; i < arrSize; i++) {
		childRow = boardCharToIndex(positionsArr->positions[i][0]);
		childCol = boardCharToIndex(positionsArr->positions[i][1]);

		if (!usedPaths[childRow][childCol]) {
			if (curListCell == NULL) { /*first node*/
				tn->next_possible_positions = curListCell = makeListCell(NULL, NULL);
			}
			else {
				curListCell->next = makeListCell(NULL, NULL);
				curListCell = curListCell->next;
			}
			curListCell->node = makeTreeNode(positionsArr->positions[i]);
			usedPaths[childRow][childCol] = TRUE;
			makePathTree(curListCell->node, usedPaths, boardArr);
		}
	}
	usedPaths[parentRow][parentCol] = FALSE;

}

treeNodeListCell* makeListCell(treeNodeListCell* next, treeNode* node) {
	treeNodeListCell* listCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));

	if (listCell == NULL) {
		printf("Memory Allocation Failure!\n");
		exit(1);
	}
	else {
		listCell->next = next;
		listCell->node = node;
	}
	return listCell;
}

treeNode* makeTreeNode(chessPos position) {
	treeNode* dataTn = (treeNode*)malloc(sizeof(treeNode));

	if (dataTn == NULL) {
		printf("Memory Allocation Failure!\n");
		exit(1);
	}
	else {
		dataTn->next_possible_positions = NULL;
		dataTn->position[0] = position[0];
		dataTn->position[1] = position[1];
	}
	return dataTn;
}

void freePathTree(pathTree tr) {
	if (tr.root != NULL)
		freePathTreeHelper(tr.root);
}

void freePathTreeHelper(treeNode* tn) {
	treeNodeListCell* Saver, *lstNode;
	if (tn == NULL)
		return;

	lstNode = tn->next_possible_positions;


	while (lstNode != NULL) {
		Saver = lstNode;
		freePathTreeHelper(lstNode->node);
		lstNode = lstNode->next;
		free(Saver);
	}

	free(tn);
}

void freeChessPosArray(chessPosArray*** boardArr) {
	int i, j;

	for (i = 0; i < SIZE_BOARD; i++) {
		for (j = 0; j < SIZE_BOARD; j++)
			free(boardArr[i][j]);
		free(boardArr[i]);
	}

	free(boardArr);
}

//check
void printPossiblePositions(treeNode* root) {
	treeNodeListCell* curCell = NULL;
	if (root == NULL) {
		return;
	}
	curCell = root->next_possible_positions;

	printf("(%c,%c) ", root->position[0], root->position[1]);

	if (curCell != NULL)
		printPossiblePositions(curCell->node);
}


#endif