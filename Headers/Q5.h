#ifndef Q5_H
#define Q5_H
void saveListToBinFile(char* file_name, chessPosList* pos_list);
BYTE conversion(char ch);
void openFileCheckSuccess(FILE* fp);
void fillZeroes(FILE* fp, int numOfBytes);
BYTE* createArrFromList(chessPosList* lst, int* size, short int* sizeOfNodes);
void threeBitsToFile(FILE* fp, BYTE* arr, int arr_size);
int numOfBytesNeeded(int arr_size);
#endif