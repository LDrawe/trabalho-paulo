#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "tela.h"
#include "algebra.h"

// desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto)
{
    float ponto1 = 1;
    float ponto2 = 2;
    SDL_RenderDrawLine(renderer, 1, 1, 300, 300);
    // desenhaArestaTela(renderer, &ponto1, &ponto2);
    // for (int i = 0; i < objeto->nArestas; i++)
    // {
    // }
}

int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL não inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("Hello SDL World!");

    if (window == NULL)
    {
        printf("SDL não criou a janela! SDL Erro: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event windowEvent;

    while (1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // ESCREVA AQUI O SEU PROGRAMA
        tObjeto3d *cubo = carregaObjeto("./src/assets/cubo.dcg");
        float **matriz = criaIdentidade4d();
        desenhaObjetoTela(renderer, matriz, cubo);

        SDL_RenderPresent(renderer);
    }

    desalocaTela(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}