#ifndef GAMEMANAGEMENT_H_INCLUDED
#define GAMEMANAGEMENT_H_INCLUDED
#include<stdbool.h>
#include "dinTomb.h"
#include "gameCycle.h"
int loadGame(int *kertSor,int *kertOszlop,int *penz, player* p1, char *save_file);
bool saveGame(int kertSor,int kertOszlop, int **kertAdat,int penz, int playerX, int playerY);
bool readTo2DArray(int *arr[], int rows, int cols);
void changeScene(int select, int *currentScene);
#endif // GAMEMANAGEMENT_H_INCLUDED
