#include <SDL2/SDL.h>
#include <stdbool.h>
//Funkció:
//  -ellenõrzi, hogy elég közel van-e a játékos a megadott négyzettõl
//Paraméterként kapja:
//  -x,y(int)               koordinátája a pontnak amihez ellenõrzünk
//  -rect(SDL_Rect)         kocka amiben allenõrizzük benne van-e a koordináta
// Visszatérési érték:      igaz/hamis (benne van/nincs benne)
// Megjegyzés: nincs
bool inReach(int x, int y, SDL_Rect rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        return true; // Point is inside one of the rectangles
    return false; // Point is not inside any of the rectangles
}

int melyikGomb(int x, int y, SDL_Rect* menuButtons)
{
    int gombokSzama=sizeof(menuButtons);
    for (int i = 0; i < gombokSzama; i++)
    {
        SDL_Rect rect = menuButtons[i];
        if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        {
            return i; // Point is inside one of the rectangles
        }
    }
    return -1; // Point is not inside any of the rectangles
}
