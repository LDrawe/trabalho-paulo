#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "tela.h"
#include "objeto.h"
#include "algebra.h"

// Aloca a tela utilizando o título passado como parâmetro e as largura e altura definidas no tela.h
SDL_Window *criaTela(const char *titulo)
{
    return SDL_CreateWindow(titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
}

// Desenha um segmento de reta na tela
void desenhaArestaTela(SDL_Renderer *renderer, float *ponto1, float *ponto2)
{
    float escala = (float)fmin(WIDTH, HEIGHT) / 20;

    // Calcula o offset para centralizar o objeto
    int offsetX = WIDTH / 2;
    int offsetY = HEIGHT / 2;

    int x1 = (int)(ponto1[0] * escala) + offsetX;
    int y1 = (int)(ponto1[1] * escala) + offsetY;
    int x2 = (int)(ponto2[0] * escala) + offsetX;
    int y2 = (int)(ponto2[1] * escala) + offsetY;

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto)
{
    int ponto1Index, ponto2Index;
    float *ponto1, *ponto2;

    for (int i = 0; i < objeto->nArestas; i++)
    {
        ponto1Index = objeto->arestas[i][0];
        ponto2Index = objeto->arestas[i][1];
        ponto1 = multMatriz4dPonto(objeto->modelMatrix, objeto->pontos[ponto1Index]);
        ponto2 = multMatriz4dPonto(objeto->modelMatrix, objeto->pontos[ponto2Index]);
        printf("ponto: %.2f %.2f %.2f\n", objeto->pontos[ponto1Index][0], objeto->pontos[ponto1Index][1], objeto->pontos[ponto1Index][2]);
        printf("ponto multiplicado: %.2f %.2f %.2f %.2f\n", ponto1[0], ponto1[1], ponto1[2], ponto1[3]);

        desenhaArestaTela(renderer, ponto1, ponto2);
        free(ponto1);
        free(ponto2);
    }
}

// Desaloca a tela
void desalocaTela(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}