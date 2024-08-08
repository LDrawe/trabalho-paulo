#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"

// Lê as informações de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(const char *nomeArquivo)
{
    int i, j;
    FILE *arquivoObj;
    tObjeto3d *novoObjeto;

    arquivoObj = fopen(nomeArquivo, "r");

    if (arquivoObj == NULL)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    novoObjeto = (tObjeto3d *)malloc(sizeof(tObjeto3d));

    fscanf(arquivoObj, "%d", &(novoObjeto->nPontos));

    novoObjeto->pontos = (float **)malloc(novoObjeto->nPontos * sizeof(float *));

    for (i = 0; i < novoObjeto->nPontos; i++)
    {
        novoObjeto->pontos[i] = (float *)malloc(4 * sizeof(float));
        fscanf(arquivoObj, "%f %f %f", &(novoObjeto->pontos[i][0]), &(novoObjeto->pontos[i][1]), &(novoObjeto->pontos[i][2]));
        novoObjeto->pontos[i][3] = 1;
    }

    fscanf(arquivoObj, "%d", &(novoObjeto->nArestas));
    novoObjeto->arestas = (int **)malloc(novoObjeto->nArestas * sizeof(int *));

    for (i = 0; i < novoObjeto->nArestas; i++)
    {
        novoObjeto->arestas[i] = (int *)malloc(2 * sizeof(int));
        fscanf(arquivoObj, "%d %d", &(novoObjeto->arestas[i][0]), &(novoObjeto->arestas[i][1]));
    }

    novoObjeto->modelMatrix = (float **)malloc(4 * sizeof(float *));

    for (i = 0; i < 4; i++)
    {
        novoObjeto->modelMatrix[i] = (float *)malloc(4 * sizeof(float));
        for (j = 0; j < 4; j++)
            if (i == j)
                novoObjeto->modelMatrix[i][j] = 1.0;
            else
                novoObjeto->modelMatrix[i][j] = 0.0;
    }

    return novoObjeto;
}

// Altera a modelMatrix de um objeto para redimenciona-lo segundo os parâmetros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ)
{
}

// Altera a modelMatrix de um objeto para translada-lo segundo os parâmetros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ)
{
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo informado
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo)
{
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo)
{
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo)
{
}

// Imprime um objeto no terminal
void imprimeObjetoDBG(tObjeto3d *objeto)
{
    if (objeto == NULL)
    {
        printf("ERRO: Objeto nulo!\n");
        return;
    }

    printf("Pontos:\n");

    for (int i = 0; i < objeto->nPontos; i++)
        printf(" [%d] - (%8.4f, %8.4f, %8.4f)\n", i, objeto->pontos[i][0], objeto->pontos[i][1], objeto->pontos[i][2]);

    printf("Arestas\n");

    for (int i = 0; i < objeto->nArestas; i++)
        printf(" [%d] - (%3d, %3d)\n", i, objeto->arestas[i][0], objeto->arestas[i][1]);

    printf("ModelMatrix:\n");
}

// Desaloca o objeto
void desalocaObjeto(tObjeto3d *objeto)
{
    if (objeto == NULL)
        return perror("Erro: objeto nulo");

    for (int i = 0; i < objeto->nPontos; i++)
        free(objeto->pontos[i]);
    free(objeto->pontos);

    for (int i = 0; i < objeto->nArestas; i++)
        free(objeto->arestas[i]);
    free(objeto->arestas);

    for (int i = 0; i < 4; i++)
        free(objeto->modelMatrix[i]);
    free(objeto->modelMatrix);
    free(objeto);
}