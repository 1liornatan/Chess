#ifndef Q1_H
#define Q1_H
void addPosToArr(chessPosArray* posArr, int i, int j);
BOOL isValidPos(int i, int j);
chessPosArray* getPositionsArr(int i, int j);
void setKnightMoves(chessPosArray*** boardArr);
chessPosArray*** validKnightMoves();
#endif