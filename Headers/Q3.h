#ifndef Q3_H
#define Q3_H
treeNode* makeTreeNode(chessPos position);
treeNodeListCell* makeListCell(treeNodeListCell* next, treeNode* node);
void makePathTree(treeNode* tn, BOOL usedPaths[SIZE_BOARD][SIZE_BOARD], chessPosArray*** boardArr);
int boardCharToIndex(char ch);
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
BOOL isDigit(char ch);
void printPossiblePositions(treeNode* root);
void freePathTree(pathTree tr);
void freePathTreeHelper(treeNode* tn);
void freeChessPosArray(chessPosArray*** boardArr);
#endif