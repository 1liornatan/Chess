#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//colors
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define PINK "\x1b[35m"
#define RESET "\x1b[0m"
//size
#define SIZE_BOARD 5
#define SIZE_ARR 1
//path
#define FILE_NOT_FOUND -1
#define NOT_VALID_PATH 1
#define PATH_COVERS_ALL_BOARD 2
#define NO_COVER_PATH_FOUND 3
//parameters
#define TRUE 1
#define FALSE 0
#define ON TRUE
#define OFF FALSE
#define EXIT 6
#endif