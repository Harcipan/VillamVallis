#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED

#include "GameCycle.h"

void gamekeyDown(SDL_Event event, DinTomb *kertTartalma, player* p1, int *isSetting,char* save_file);
void gamekeyUp(SDL_Event event, player* p1);
void movePlayer(player* p1);
void handle_keyboard_event(SDL_Event *event, char *inputText);

#endif // GAMEINPUT_H_INCLUDED
