#include "ManagementGame.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "DinTomb.h"
#include "GameCycle.h"

//  Funkció:  Ellenőrzi, hogy a 'sztring' végződik-e a 'veg' sztringre.
//  Paraméterek:
//    - sztring: az ellenőrizendő sztring.
//    - veg: a végződés, amit keresünk.
//  Visszatérési érték: igaz (1), ha a sztring a 'veg' sztringre végződik, egyébként hamis (0).

int endsWith(const char *sztring, const char *veg)
{
    if (!sztring || !veg)
    {
        return false;
    }
    size_t sztringHossz = strlen(sztring);
    size_t vegHossz = strlen(veg);
    if (vegHossz > sztringHossz)
    {
        return false;
    }
    return strncmp(sztring + sztringHossz - vegHossz, veg, vegHossz) == 0;
}


//  Hozzáfűzi a ".txt" kiterjesztést a 'fajlnev'-hez, ha még nem tartalmazza.
//  Paraméterek:
//  - fajlnev: a fájl neve, amelyhez hozzá szeretnénk fűzni a kiterjesztést.
//  - maxMeret: a 'fajlnev' puffer maximális mérete.
//
void appendTxtExtension(char *fajlnev, size_t maxMeret)
{
    const char *kiterjesztes = ".txt";
    if (!endsWith(fajlnev, kiterjesztes))
    {
        if (strlen(fajlnev) + strlen(kiterjesztes) < maxMeret)
        {
            strcat(fajlnev, kiterjesztes);
        }
    }
}


// Létrehoz egy új fájlnevet a megadott 'eredeti' fájlnévből, hozzáfűzve a ".txt" kiterjesztést és a "saves/" mappanevet.
// Paraméterek:
//   - eredeti: az eredeti fájlnév.
//   - puffer: a létrehozott új fájlnév tárolására szolgáló puffer.
//   - pufferMeret: a 'puffer' maximális mérete.
//
void getFileNameWithExtension(const char *eredeti, char *puffer, size_t pufferMeret)
{
    const char *mappa = "saves/";
    const char *kiterjesztes = ".txt";
    if (strlen(eredeti) + strlen(kiterjesztes) < pufferMeret)
    {
        strcpy(puffer, mappa);
        strcat(puffer, eredeti);
        if (!endsWith(puffer, kiterjesztes))
        {
            strcat(puffer, kiterjesztes);
        }
    }
}

// Funkció:
//  - Betölti a játékállást a paraméterként kapott változókba a megadott file-ból
// Paraméterként kapja:
//  - kertSor/Oszlop(int)    kert méretét meghatározó paraméterek
//  - penz(int)              játékos pénze kert bõvítéséhez (+egyéb vásárlásokhoz kell)
//  - p1(player)             játékos pozícióját, sebességét tartalmazó struktúra
//  - save_file(char)        melyik mentett állást töltse be a program
// Visszatérési érték: sikeres volt-e a betöltés
// Megjegyzés: nincs
bool loadGame(int *kertSor, int *kertOszlop, player *p1, char *save_file)
{
    // Játék betöltése
    // Deklaráljunk egy FILE mutatót a fájl kezeléséhez
    FILE *file;
    char filenameWithExtension[256];
    getFileNameWithExtension(save_file, filenameWithExtension, sizeof(filenameWithExtension));
    // Nyissuk meg a fájlt olvasásra
    file = fopen(filenameWithExtension, "r");

    // Ellenõrizzük, hogy a fájlt sikeresen megnyitottuk-e
    if (file == NULL)
    {
        printf("Nem sikerult megnyitni a fajlt.\n");
        return false;
    }

    // Olvassuk és nyomtassuk ki a fájl tartalmát soronként
    char line[100]; // A puffer méretét igény szerint módosíthatjuk

    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
        if (strstr(line, "kertSor:") != NULL)
        {
            // Keressük meg a "kertSor:" szóval kezdõdõ sort
            char *numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // A kettõspont utáni számot dolgozzuk fel
                *kertSor = atoi(numberStr + 1);
            }
        }
        if (strstr(line, "kertOszlop:") != NULL)
        {
            // Keressük meg a "kertOszlop:" szóval kezdõdõ sort
            char *numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // A kettõspont utáni számot dolgozzuk fel
                *kertOszlop = atoi(numberStr + 1);
            }
        }
        if (strstr(line, "penz:") != NULL)
        {
            // Keressük meg a "penz:" szóval kezdõdõ sort
            char *numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // A kettõspont utáni számot dolgozzuk fel
                p1->penz = atoi(numberStr + 1);
            }
        }
        if (strstr(line, "playerPosX:") != NULL)
        {
            // Keressük meg a "playerPosX:" szóval kezdõdõ sort
            char *numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // A kettõspont utáni számot dolgozzuk fel
                p1->playerX = atoi(numberStr + 1);
            }
        }
        if (strstr(line, "playerPosY:") != NULL)
        {
            // Keressük meg a "playerPosY:" szóval kezdõdõ sort
            char *numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // A kettõspont utáni számot dolgozzuk fel
                p1->playerY = atoi(numberStr + 1);
                printf("%d", p1->playerY);
            }
        }
    }

    // Zárjuk le a fájlt, amikor végeztünk vele
    fclose(file);
    return true;
}

// Funkció:
//  - Beolvassa a kertben elültetett növények állapotát a mentett állásból
// Paraméterként kapja:
//  - arr(int)           2D-s tömb amiben kert állapotát tároljuk
//  - rows/cols(int)    kert mérete (sor, oszlop)
//  - save_file(char)   a kiválasztott mentésfile amibol betölt
// Visszatérési érték: sikerült-e a beolvasás
bool readTo2DArray(int *arr[], int rows, int cols, char* save_file)
{
    char filenameWithExtension[256];
    getFileNameWithExtension(save_file, filenameWithExtension, sizeof(filenameWithExtension));

    FILE *file = fopen(filenameWithExtension, "r");
    if (file == NULL)
    {
        printf("Hiba a fajl megnyitásakor!\n");
        return false;
    }

    char line[1024]; // Maximalizáljuk a sor hosszát 1024 karakterre
    int row = 0;
    int dataStarted = false;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Ellenõrizzük, hogy a sor tartalmazza-e a "kertAdat" szót
        if (strstr(line, "kertAdat") != NULL)
        {
            dataStarted = true;
            continue; // Ugorjunk át erre a sorra és kezdjük el a következõ feldolgozását
        }

        // Ha a dataStarted 1, akkor dolgozzuk fel a sort
        if (dataStarted)
        {
            char *token = strtok(line, ",");
            int col = 0;
            while (token != NULL && col < cols && row < rows)
            {
                arr[row][col] = atoi(token);
                token = strtok(NULL, ",");
                col++;
            }
            row++;
        }
    }

    fclose(file);
    return true;
}

// Funkció:
//  - Elmenti a játékállást a megadott mentésfile-ba
// Paraméterként kapja:
//  - kertSor/Oszlop(int)    kert méretét meghatározó paraméterek
//  - kertAdat               kert tartalmát tartalmazó 2D tömb
//  - penz(int)              játékos pénze kert bõvítéséhez (+egyéb vásárlásokhoz kell)
//  - p1(player)             játékos pozícióját, sebességét tartalmazó struktúra
//  - save_file(char)        melyik mentésfilera töltse be
// Visszatérési érték:      sikerült-e vagy nem a mentés
bool saveGame(int kertSor, int kertOszlop, int **kertAdat, player* p1,char* save_file)
{
    FILE *file;
    char filenameWithExtension[256];
    getFileNameWithExtension(save_file, filenameWithExtension, sizeof(filenameWithExtension));
    // Nyissuk meg a fájlt írásra
    file = fopen(filenameWithExtension, "w");

    // Ellenõrizzük, hogy a fájlt sikeresen megnyitottuk-e
    if (file == NULL)
    {
        printf("Nem sikerult megnyitni a fajlt.\n");
        return false;
    }

    // Írjuk ki a kertSor és kertOszlop értékeit a fájlba
    fprintf(file, "kertSor: %d\n", kertSor);
    fprintf(file, "kertOszlop: %d\n", kertOszlop);
    fprintf(file, "penz: %d\n", p1->penz);
    fprintf(file, "playerPosX: %d\n", p1->playerX);
    fprintf(file, "playerPosY: %d\n", p1->playerY);
    // Írjuk ki a "kertAdat:" szöveget a fájlba
    fprintf(file, "kertAdat:");
    fprintf(file, "\n");
    // Írjuk ki a kertAdat elemeit egymás után
    for (int i = 0; i < kertSor; i++)
    {
        for (int j = 0; j < kertOszlop; j++)
        {
            fprintf(file, "%d,", kertAdat[i][j]);
        }
        fprintf(file, "\n");
    }

    // Írjunk egy új sort a kertAdat elemeinek végén
    fprintf(file, "\n");

    // Zárjuk le a fájlt
    fclose(file);

    printf("\nA mentes sikeres volt.\n");

    return true;
}

//Funkció vált a scenek (menu, gameplay) között
// Paraméterként kapja:
//  - select    melyik scenere váltson
//  - currentScene ennek megváltoztatásával tudja a gamecyle, hogy váltson

void changeScene(int select, int *currentScene)
{
    if (select == 1)
    {
        *currentScene = 2;
    }
    else
    {
        *currentScene = 1;
    }
}
