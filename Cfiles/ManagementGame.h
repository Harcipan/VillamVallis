#ifndef GAMEMANAGEMENT_H_INCLUDED
#define GAMEMANAGEMENT_H_INCLUDED

#include<stdbool.h>
#include "DinTomb.h"
#include "GameCycle.h"

bool loadGame(int *kertSor,int *kertOszlop, player* p1, char *save_file);
bool saveGame(int kertSor, int kertOszlop, int **kertAdat, player* p1,char* save_file);
bool readTo2DArray(int *arr[], int rows, int cols, char* save_file);
void changeScene(int select, int *currentScene);

#endif // GAMEMANAGEMENT_H_INCLUDED
