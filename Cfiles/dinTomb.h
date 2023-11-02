#ifndef DINTOMB_H_INCLUDED
#define DINTOMB_H_INCLUDED
#include<stdbool.h>
#include <SDL2/SDL.h>
typedef struct DinTomb
{
    int **adat;
    int meretSor;//hany darab sor van
    int meretOszlop;//hany darab oszlop van
} DinTomb;
bool dintomb_atmeretez(DinTomb *kertTartalma, int ujmeretSor, int ujmeretOszlop);
bool dintomb_foglal(DinTomb *kertTartalma, int meretSor, int meretOszlop);
void dintomb_feltolt(DinTomb *kertTartalma, int meretSor, int meretOszlop,int tolto);
void memoryCleanup(DinTomb *kertTartalma,SDL_Texture *novenyek,SDL_Texture *playerText);//

#endif // DINTOMB_H_INCLUDED
