#ifndef DINTOMB_H_INCLUDED
#define DINTOMB_H_INCLUDED
#include<stdbool.h>
typedef struct DinTomb
{
    int **adat;
    int meretSor;//hany darab sor van
    int meretOszlop;//hany darab oszlop van
} DinTomb;
bool dintomb_atmeretez(DinTomb *kertTartalma, int ujmeretSor, int ujmeretOszlop);
bool dintomb_foglal(DinTomb *kertTartalma, int meretSor, int meretOszlop);
void dintomb_feltolt(DinTomb *kertTartalma, int meretSor, int meretOszlop,int tolto);

#endif // DINTOMB_H_INCLUDED
