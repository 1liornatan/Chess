#ifndef Q4_FUNCTIONS_C
#define Q4_FUNCTIONS_C
#include "Header.h"
#include "Typedef.h"
#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
	chessPosList* completePathLst = (chessPosList*)malloc(sizeof(chessPosList));;

	if (completePathLst == NULL) {
		printf("Memory Allocation Failure!\n");
		exit(1);
	}

	makeEmptyList(completePathLst);

	if (findKnightPathCoveringAllBoardHelper(path_tree->root, completePathLst, 1) == TRUE) {
		insertDataToStartList(completePathLst, path_tree->root->position);
		return completePathLst;
	}
	return NULL;
}

BOOL findKnightPathCoveringAllBoardHelper(treeNode* tn, chessPosList* path_list, int pathSize) {
	treeNodeListCell* treeLevelLstNode;
	BOOL path_flag = FALSE;

	if (pathSize == (SIZE_BOARD * SIZE_BOARD))
		return TRUE;
	else if (tn == NULL)
		return FALSE;

	treeLevelLstNode = tn->next_possible_positions;

	while (treeLevelLstNode != NULL && path_flag == FALSE) {
		path_flag = findKnightPathCoveringAllBoardHelper(treeLevelLstNode->node, path_list, pathSize + 1);
		if (path_flag == TRUE)
			insertDataToStartList(path_list, treeLevelLstNode->node->position);
		treeLevelLstNode = treeLevelLstNode->next;
	}

	return path_flag;
}

void makeEmptyList(chessPosList* lst) {
	lst->head = lst->tail = NULL;
}

void insertDataToStartList(chessPosList* lst, chessPos data) {
	chessPosCell* dataNode = (chessPosCell*)malloc(sizeof(chessPosCell));

	if (dataNode == NULL) {
		printf("Memory Allocation Failure!\n");
		exit(1);
	}

	dataNode->next = NULL;
	dataNode->position[0] = data[0];
	dataNode->position[1] = data[1];

	insertNodeToStartList(lst, dataNode);
}

void insertNodeToStartList(chessPosList* lst, chessPosCell* dataNode) {
	if (isEmptyList(lst) == TRUE)
		lst->head = lst->tail = dataNode;
	else {
		dataNode->next = lst->head;
		lst->head = dataNode;
	}
}

BOOL isEmptyList(chessPosList* lst) {
	return (lst->head == NULL);
}
//check
void printFullPath(chessPosList* lst) {
	chessPosCell* currNode;
	if (lst == NULL)
		printf("NO PATH\n");
	else if (isEmptyList(lst) == TRUE)
		printf("EMPTY");
	else {
		currNode = lst->head;
		printf("Full Board Path:\n");
		while (currNode != NULL) {
			printf("(%c,%c) ", currNode->position[0], currNode->position[1]);
			currNode = currNode->next;
		}
	}
}
#endif