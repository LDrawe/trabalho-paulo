#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "tela.h"
#include "algebra.h"

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
    tObjeto3d *cubo = carregaObjeto("./src/assets/cubo.dcg");
    float **matriz = criaIdentidade4d();
    imprimeObjetoDBG(cubo);

    while (RUNNING)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // ESCREVA AQUI O SEU PROGRAMA
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_UP])
        {
            transladaObjeto(cubo, 0.0f, -0.1f, 0.0f);
        }

        if (state[SDL_SCANCODE_DOWN])
        {
            transladaObjeto(cubo, 0.0f, 0.1f, 0.0f);
        }

        if (state[SDL_SCANCODE_RIGHT])
        {
            transladaObjeto(cubo, 0.1f, 0.0f, 0.0f);
        }

        if (state[SDL_SCANCODE_LEFT])
        {
            transladaObjeto(cubo, -0.1f, 0.0f, 0.0f);
        }

        if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_RIGHT])
        {
            escalaObjeto(cubo, 0.05f, 0.0f, 0.0f);
        }

        if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_LEFT])
        {
            escalaObjeto(cubo, -0.05f, 0.0f, 0.0f);
        }

        if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_UP])
        {
            escalaObjeto(cubo, 0.0f, 0.05f, 0.0f);
        }

        if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_DOWN])
        {
            escalaObjeto(cubo, 0.0f, -0.05f, 0.0f);
        }

        desenhaObjetoTela(renderer, matriz, cubo);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    desalocaObjeto(cubo);
    desalocaTela(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}