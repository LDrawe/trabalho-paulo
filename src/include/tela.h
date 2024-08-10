#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"

#define WIDTH 800
#define HEIGHT 600
#define RUNNING 1

//Aloca a tela utilizando o título passado como parâmetro e as largura e altura definidas no tela.h
SDL_Window* criaTela(const char* titulo);

//Desenha um segmento de reta na tela
void desenhaArestaTela(SDL_Renderer* renderer, float* ponto1, float* ponto2);

// Desenha um objeto inteiro na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto);

//Desaloca a tela
void desalocaTela(SDL_Window* window);
