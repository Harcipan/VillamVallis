#include <SDL2/SDL_ttf.h>
#include "szoveg_kiir.h"

void szoveg_kiir(int penz, SDL_Renderer *renderer){
    // betutipus betoltese, 32 pont magassaggal
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Lato-Bold.ttf", 32);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    char textBuffer[50]; // Adjust the buffer size as needed
    snprintf(textBuffer, sizeof(textBuffer), "Pontok Lacikám, pontok: %d", penz); // Convert the variable to a string

    // felirat megrajzolasa, kulonfele verziokban
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };
    SDL_Color feher = {255, 255, 255}, piros = {255, 0, 0};
    // ha sajat kodban hasznalod, csinalj belole fuggvenyt!
    felirat = TTF_RenderUTF8_Solid(font, textBuffer, feher);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (800 - felirat->w) / 2;
    hova.y = 360;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}
