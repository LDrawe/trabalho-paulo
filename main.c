#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "tela.h"
#include "algebra.h"

// Função para processar eventos de teclado
void processaInput(tObjeto3d *cubo)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP])
        transladaObjeto(cubo, 0.0f, -0.1f, 0.0f);

    if (state[SDL_SCANCODE_DOWN])
        transladaObjeto(cubo, 0.0f, 0.1f, 0.0f);

    if (state[SDL_SCANCODE_RIGHT])
        transladaObjeto(cubo, 0.1f, 0.0f, 0.0f);

    if (state[SDL_SCANCODE_LEFT])
        transladaObjeto(cubo, -0.1f, 0.0f, 0.0f);

    if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_RIGHT])
        escalaObjeto(cubo, 0.05f, 0.0f, 0.0f);

    if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_LEFT])
        escalaObjeto(cubo, -0.05f, 0.0f, 0.0f);

    if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_UP])
        escalaObjeto(cubo, 0.0f, 0.05f, 0.0f);

    if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_DOWN])
        escalaObjeto(cubo, 0.0f, -0.05f, 0.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_UP])
        rotacionaObjeto(cubo, 'X', 1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        rotacionaObjeto(cubo, 'X', -1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        rotacionaObjeto(cubo, 'Y', 1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        rotacionaObjeto(cubo, 'Y', -1.0f);

    if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_RIGHT])
        rotacionaObjeto(cubo, 'Z', 1.0f);

    if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_LEFT])
        rotacionaObjeto(cubo, 'Z', -1.0f);
}

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
