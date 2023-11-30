#include <SDL2/SDL_ttf.h>

//Funkció:
//  -kiír egy megadott szöveget megadott pozícióba
//Paraméterként kapja:
//  -x,y(int)               koordinátája a pontnak ahova ír
//  -rect(SDL_Rect)         kocka amiben allenõrizzük benne van-e a koordináta
// Visszatérési érték:      igaz/hamis (benne van/nincs benne)
// Megjegyzés:              a hívónak ki kell lépnie a TTF-bol
void szoveg_kiir(SDL_Renderer *renderer,char* szoveg,int posX,int posY,int alignX,int alignY)
{
    // betutipus betoltese, 32 pont magassaggal
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Fonts/Lato-Bold.ttf", 32);
    if (!font)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        SDL_Delay(60000);//60s wait, debug segítség
        exit(1);
    }

    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };
    SDL_Color feher = {255, 255, 255};
    felirat = TTF_RenderUTF8_Solid(font, szoveg, feher);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    if(alignX)
    {
        hova.x = posX-felirat->w;
    }
    else
    {
        hova.x = posX;

    }


    if(alignY)
    {
        hova.y = posY-felirat->h;
    }
    else
    {
        hova.y = posY;
    }



    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}
