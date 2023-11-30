#include "GameCycle.h"

////Funkció:
////  -beállítja a következo mozgásanimációt
////Paraméterként kapja:
////  -p1 (játékos adatait mint jelenlegi irányítottság és animáció fázisa)
void playerOrient(player* p1)
{
    if (p1->up || p1->down || p1->left || p1->right)
    {
        // Movement states
        if (p1->up && p1->right)
        {
            p1->pOrientation = (p1->pOrientation == MovUR1) ? MovUR2 : MovUR1;
        }
        else if (p1->up && p1->left)
        {
            p1->pOrientation = (p1->pOrientation == MovUL1) ? MovUL2 : MovUL1;
        }
        else if (p1->down && p1->right)
        {
            p1->pOrientation = (p1->pOrientation == MovDR1) ? MovDR2 : MovDR1;
        }
        else if (p1->down && p1->left)
        {
            p1->pOrientation = (p1->pOrientation == MovDL1) ? MovDL2 : MovDL1;
        }
        else if (p1->right)
        {
            p1->pOrientation = (p1->pOrientation == MovR1) ? MovR2 : MovR1;
        }
        else if (p1->left)
        {
            p1->pOrientation = (p1->pOrientation == MovL1) ? MovL2 : MovL1;
        }
        else if (p1->up)
        {
            p1->pOrientation = (p1->pOrientation == MovU1) ? MovU2 : MovU1;
        }
        else if (p1->down)
        {
            p1->pOrientation = (p1->pOrientation == MovD1) ? MovD2 : MovD1;
        }
    }
    else
    {
        // Back to idle
        if( p1->pOrientation%4>2)
        {
            p1->pOrientation-=p1->pOrientation%4-2;
        }
        // idle statek kozott valtas
        if (p1->pOrientation % 4 == 0)
        {
            p1->pOrientation += 1;
        }
        else
        {
            p1->pOrientation -= 1;
        }
    }
}
