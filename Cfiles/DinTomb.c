#include "dinTomb.h"
#include<stdbool.h>
#include<stdlib.h>
#include "debugmalloc.h"
#include <SDL2/SDL.h>

//Funkció:
//  -atmeretez egy megadott dinamikus 2D tombot, megadott sor és osszlop nagyságúra
//Paraméterként kapja:
//  -ketDinTomb(DinTomb)    2D dinamikusan foglalt tomb adatait tároló struct
//  -ujmeretSor/Oszlop(int) mennyi sor és oszlop legyen az újonnan foglalt tömbben
//Visszatérési érték:
//  -sikeres/nem(bool)      átméretezés sikerült-e
//Megjegyzés                a lefoglalt területet a hívónak kell felszabadítani
bool dintomb_atmeretez(DinTomb *ketDinTomb, int ujmeretSor, int ujmeretOszlop)
{
    int **ujadat = (int **)malloc(ujmeretSor * sizeof(int *));
    if (ujadat == NULL)
        return false;

    for (int i = 0; i < ujmeretSor; ++i)
    {
        ujadat[i] = (int *)malloc(ujmeretOszlop * sizeof(int));
        if (ujadat[i] == NULL)
        {
            // Ha hiba van felszabadítja a már lefoglalt memóriát
            for (int j = 0; j < i; ++j)
            {
                free(ujadat[j]);
            }
            free(ujadat);
            return false;
        }
    }

    // Calculate the minimum dimensions to copy from the old data
    int minSor = ujmeretSor < ketDinTomb->meretSor ? ujmeretSor : ketDinTomb->meretSor;
    int minOszlop = ujmeretOszlop < ketDinTomb->meretOszlop ? ujmeretOszlop : ketDinTomb->meretOszlop;

    // Copy data from the old array to the new array
    for (int i = 0; i < minSor; ++i)
    {
        for (int j = 0; j < minOszlop; ++j)
        {
            ujadat[i][j] = ketDinTomb->adat[i][j];
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
    for (int i = 0; i < ketDinTomb->meretSor; ++i)
    {
        free(ketDinTomb->adat[i]);
    }
    free(ketDinTomb->adat);

    // Update the structure with the new data and dimensions
    ketDinTomb->adat = ujadat;
    ketDinTomb->meretSor = ujmeretSor;
    ketDinTomb->meretOszlop = ujmeretOszlop;

    return true;
}

//Funkció:
//  -lefoglal egy megadott dinamikus 2D tombot, megadott sor és osszlop nagyságúra
//Paraméterként kapja:
//  -ketDinTomb(DinTomb)    2D dinamikusan foglalt tomb adatait tároló struct
//  -meretSor/Oszlop(int)   mennyi sor és oszlop legyen a lefoglalandó tömbben
//Visszatérési érték:
//  -sikeres/nem(bool)      lefoglalás sikerült-e
//Megjegyzés                a lefoglalt területet a hívónak kell felszabadítani
bool dintomb_foglal(DinTomb *ketDinTomb, int meretSor, int meretOszlop)
{
    ketDinTomb->meretSor = meretSor;
    ketDinTomb->meretOszlop = meretOszlop;
    ketDinTomb->adat = (int**)malloc(meretSor * sizeof(int*));
    if (ketDinTomb->adat == NULL)
    {
        return false;
    }

    for (int i = 0; i < meretSor; ++i)
    {
        ketDinTomb->adat[i] = (int*)malloc(meretOszlop * sizeof(int));
        if (ketDinTomb->adat[i] == NULL)
        {
            // Handle allocation failure and free previously allocated memory.
            for (int j = 0; j < i; ++j)
            {
                free(ketDinTomb->adat[j]);
            }
            free(ketDinTomb->adat);
            return false;
        }
    }

    return true;
}

//Funkció:
//  -feltölt egy megadott dinamikus 2D tombot, megadott számmal
//Paraméterként kapja:
//  -ketDinTomb(DinTomb)    2D dinamikusan foglalt tomb adatait tároló struct
//  -meretSor/Oszlop(int)   mennyi sor és oszlop legyen az újonnan foglalt tömbben
void dintomb_feltolt(DinTomb *ketDinTomb,int tolto)
{
    for (int i = 0; i < ketDinTomb->meretSor; ++i)
    {
        for (int j = 0; j < ketDinTomb->meretOszlop; ++j)
        {
            ketDinTomb->adat[i][j] = tolto;
        }
    }
}

//Funkció:
//  -felszabadítja a lefoglalt területeket
//Paraméterként kapja:
//  -ketDinTomb(DinTomb)    2D dinamikusan foglalt tomb adatait tároló struct
//  -novenyek(SDL_Texture)  novenyek képének textúrájára mutató ptr
//  -playerText(SDL_Texture)játékos textúrájára mutató ptr
void memoryCleanup(DinTomb *ketDinTomb,SDL_Texture *novenyek,SDL_Texture *playerText)
{
    for (int i = 0; i < ketDinTomb->meretSor; ++i)
    {
        free(ketDinTomb->adat[i]);
    }
    free(ketDinTomb->adat);
    SDL_DestroyTexture(novenyek);
    SDL_DestroyTexture(playerText);
}
