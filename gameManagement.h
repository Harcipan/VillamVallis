#ifndef GAMEMANAGEMENT_H_INCLUDED
#define GAMEMANAGEMENT_H_INCLUDED
#include<stdbool.h>
#include "dinTomb.h"
int loadGame(int *kertSor,int *kertOszlop);
bool saveGame(int kertSor,int kertOszlop, int **kertAdat);
bool readTo2DArray(int *arr[], int rows, int cols);

#endif // GAMEMANAGEMENT_H_INCLUDED
