#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "tela.h"
#include "objeto.h"
#include "algebra.h"

SDL_Window *criaTela(const char *titulo)
{
    return SDL_CreateWindow(titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
}

void desenhaArestaTela(SDL_Renderer *renderer, float *ponto1, float *ponto2)
{
    float escala = (float)fmin(WIDTH, HEIGHT) / 20;

    int x1 = (int)(ponto1[0] * escala) + WIDTH / 2;
    int y1 = (int)(ponto1[1] * escala) + HEIGHT / 2;
    int x2 = (int)(ponto2[0] * escala) + WIDTH / 2;
    int y2 = (int)(ponto2[1] * escala) + HEIGHT / 2;

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void desenhaObjetoTela(SDL_Renderer *renderer, tObjeto3d *objeto)
{
    // Precompute all transformed points
    float **pontosTransformados = (float **)malloc(objeto->nPontos * sizeof(float *));
    for (int i = 0; i < objeto->nPontos; i++)
    {
        pontosTransformados[i] = multMatriz4dPonto(objeto->modelMatrix, objeto->pontos[i]);
    }

    // Draw edges using precomputed points
    for (int i = 0; i < objeto->nArestas; i++)
    {
        float *ponto1 = pontosTransformados[objeto->arestas[i][0]];
        float *ponto2 = pontosTransformados[objeto->arestas[i][1]];

        desenhaArestaTela(renderer, ponto1, ponto2);
    }

    for (int i = 0; i < objeto->nPontos; i++)
    {
        free(pontosTransformados[i]);
    }
    free(pontosTransformados);
}

// Desaloca a tela
void desalocaTela(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}