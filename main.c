#include <stdio.h>
#include <SDL2/SDL.h>
#include "algebra.h"
#include "controls.h"
#include "objeto.h"
#include "tela.h"

// Função para renderizar o objeto na tela
void renderiza(SDL_Renderer *renderer, tObjeto3d *cubo)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    desenhaObjetoTela(renderer, cubo);

    SDL_Delay(16);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL não inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("Cubo");

    if (window == NULL)
    {
        printf("SDL não criou a janela! SDL Erro: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event windowEvent;
    tObjeto3d *cubo = carregaObjeto("./src/assets/cubo.dcg");

    while (RUNNING)
    {
        if (SDL_PollEvent(&windowEvent) && windowEvent.type == SDL_QUIT)
            break;

        processaInput(cubo);
        renderiza(renderer, cubo);
    }

    desalocaObjeto(cubo);
    desalocaTela(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
