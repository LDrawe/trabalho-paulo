#include <stdio.h>
#include <SDL2/SDL.h>
#include "algebra.h"
#include "controls.h"
#include "objeto.h"
#include "tela.h"
#include "camera.h"

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

    tCamera *camera = criaCamera();
    tProj *proj = criaProjecao(1, -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    while (RUNNING)
    {
        if (SDL_PollEvent(&windowEvent) && windowEvent.type == SDL_QUIT)
            break;

        processaInput(cubo);
        renderiza(renderer, cubo, camera->viewMatrix, proj->projectionMatrix);
    }

    desalocaObjeto(cubo);
    desalocaTela(window);
    desalocaCamera(camera);
    desalocaProjecao(proj);
    SDL_Quit();

    return EXIT_SUCCESS;
}
