#ifndef Q2_H
#define Q2_H
void falseAll(BOOL arr[][SIZE_BOARD]);
void display(chessPosList* lst);
void deleteDuplicates(chessPosList* lst);
void deleteNode(chessPosList* lst, chessPosCell* currPrev, chessPosCell* currDelete);
void BuildBoard(chessPosList* lst);
void printBoard(int board[][SIZE_BOARD]);
void printBorders();
void freeList(chessPosList* lst);
#endif