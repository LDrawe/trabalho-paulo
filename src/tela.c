#include <stdio.h>
#include <SDL2/SDL.h>
#include "tela.h"

// Aloca a tela utilizando o título passado como parâmetro e as largura e altura definidas no tela.h
SDL_Window *criaTela(const char *titulo)
{
    return SDL_CreateWindow(titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
}

// Desenha um segmento de reta na tela
void desenhaArestaTela(SDL_Renderer *renderer, float *ponto1, float *ponto2)
{
    int ponto1X, ponto1Y, ponto2X, ponto2Y;

    ponto1X = ((ponto1[0]) + 1) * WIDTH / 2;
    ponto1Y = (1 - ponto1[1]) * HEIGHT / 2;
    ponto2X = ((ponto2[0]) + 1) * WIDTH / 2;
    ponto2Y = (1 - ponto2[1]) * HEIGHT / 2;

    SDL_RenderDrawLine(renderer, ponto1X, ponto1Y, ponto2X, ponto2Y);
}

// Desaloca a tela
void desalocaTela(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}