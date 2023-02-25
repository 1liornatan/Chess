#ifndef Q4_H
#define Q4_H
BOOL isEmptyList(chessPosList* lst);
void insertNodeToStartList(chessPosList* lst, chessPosCell* dataNode);
void insertDataToStartList(chessPosList* lst, chessPos data);
void makeEmptyList(chessPosList* lst);
BOOL findKnightPathCoveringAllBoardHelper(treeNode* tn, chessPosList* path_list, int pathSize);
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void printFullPath(chessPosList* lst);
#endif