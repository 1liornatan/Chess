#ifndef Q6_H
#define Q6_H
void insertDataToEndList(chessPosList* lst, char letter, char num);
chessPosCell* createNewListNode(char letter, char num, chessPosCell* next);
void insertNodeToEndList(chessPosList* lst, chessPosCell* node);
void makeEmptyList(chessPosList* lst);
BOOL IsEmptyList(chessPosList* lst);
chessPosList getListFromFile(FILE* fp);
void openFileCheckSuccess(FILE* fp);
char conversionTochar(BYTE byte, int numParity);
int nodesToBits(short int numOfNodes);
BOOL isValidPath(chessPosArray*** knightMovesArr, chessPosList* lst);
int charLetterToIndexArr(char ch);
int charNumberToIndexArr(char num);
BOOL isPositionInKnightMovesArr(chessPosArray*** knightMovesArr, chessPosCell* curr, chessPosCell* currNext);
int checkAndDisplayPathFromFile(char* file_name);
void freeKnightMovesArr(chessPosArray*** arr);
BOOL isPathCoversAllBoard(chessPosList* lst);
void printPathState(int path_state);
void printList(chessPosList* lst);
#endif