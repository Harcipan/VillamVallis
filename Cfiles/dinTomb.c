#include "dinTomb.h"
#include<stdbool.h>
#include<stdlib.h>
#include "debugmalloc.h"


bool dintomb_atmeretez(DinTomb *kertTartalma, int ujmeretSor, int ujmeretOszlop)
{
    int **ujadat = (int **)malloc(ujmeretSor * sizeof(int *));
    if (ujadat == NULL)
        return false;

    for (int i = 0; i < ujmeretSor; ++i)
    {
        ujadat[i] = (int *)malloc(ujmeretOszlop * sizeof(int));
        if (ujadat[i] == NULL)
        {
            // Handle allocation failure and free previously allocated memory.
            for (int j = 0; j < i; ++j)
            {
                free(ujadat[j]);
            }
            free(ujadat);
            return false;
        }
    }

    // Calculate the minimum dimensions to copy from the old data
    int minSor = ujmeretSor < kertTartalma->meretSor ? ujmeretSor : kertTartalma->meretSor;
    int minOszlop = ujmeretOszlop < kertTartalma->meretOszlop ? ujmeretOszlop : kertTartalma->meretOszlop;

    // Copy data from the old array to the new array
    for (int i = 0; i < minSor; ++i)
    {
        for (int j = 0; j < minOszlop; ++j)
        {
            ujadat[i][j] = kertTartalma->adat[i][j];
        }
    }

    // Fill any remaining space in the new array with 0
    for (int i = minSor; i < ujmeretSor; ++i)
    {
        for (int j = 0; j < ujmeretOszlop; ++j)
        {
            ujadat[i][j] = 0;
        }
    }

    for (int j = minOszlop; j < ujmeretOszlop; ++j)
    {
        for (int i = 0; i < ujmeretSor; ++i)
        {
            ujadat[i][j] = 0;
        }
    }

    // Free the old data if resizing is successful
    for (int i = 0; i < kertTartalma->meretSor; ++i)
    {
        free(kertTartalma->adat[i]);
    }
    free(kertTartalma->adat);

    // Update the structure with the new data and dimensions
    kertTartalma->adat = ujadat;
    kertTartalma->meretSor = ujmeretSor;
    kertTartalma->meretOszlop = ujmeretOszlop;

    return true;
}


bool dintomb_foglal(DinTomb *kertTartalma, int meretSor, int meretOszlop)
{
    kertTartalma->meretSor = meretSor;
    kertTartalma->meretOszlop = meretOszlop;
    kertTartalma->adat = (int**)malloc(meretSor * sizeof(int*));
    if (kertTartalma->adat == NULL)
    {
        return false;
    }

    for (int i = 0; i < meretSor; ++i)
    {
        kertTartalma->adat[i] = (int*)malloc(meretOszlop * sizeof(int));
        if (kertTartalma->adat[i] == NULL)
        {
            // Handle allocation failure and free previously allocated memory.
            for (int j = 0; j < i; ++j)
            {
                free(kertTartalma->adat[j]);
            }
            free(kertTartalma->adat);
            return false;
        }
    }

    return true;
}

void dintomb_feltolt(DinTomb *kertTartalma, int meretSor, int meretOszlop,int tolto)
{
    for (int i = 0; i < meretSor; ++i)
    {
        for (int j = 0; j < meretOszlop; ++j)
        {
            kertTartalma->adat[i][j] = tolto;
        }
    }
}

void memoryCleanup(DinTomb *kertTartalma,SDL_Texture *novenyek,SDL_Texture *playerText)//,SDL_Texture *playerText
{
    for (int i = 0; i < kertTartalma->meretSor; ++i)
    {
        free(kertTartalma->adat[i]);
    }
    free(kertTartalma->adat);
    SDL_DestroyTexture(novenyek);
    SDL_DestroyTexture(playerText);
}
