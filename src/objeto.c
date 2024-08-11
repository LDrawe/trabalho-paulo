#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "algebra.h"
// Lê as informações de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(const char *nomeArquivo)
{
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

    for (int i = 0; i < novoObjeto->nPontos; i++)
    {
        novoObjeto->pontos[i] = (float *)malloc(4 * sizeof(float));
        fscanf(arquivoObj, "%f %f %f", &(novoObjeto->pontos[i][0]), &(novoObjeto->pontos[i][1]), &(novoObjeto->pontos[i][2]));
        novoObjeto->pontos[i][3] = 1;
    }

    fscanf(arquivoObj, "%d", &(novoObjeto->nArestas));
    novoObjeto->arestas = (int **)malloc(novoObjeto->nArestas * sizeof(int *));

    for (int i = 0; i < novoObjeto->nArestas; i++)
    {
        novoObjeto->arestas[i] = (int *)malloc(2 * sizeof(int));
        fscanf(arquivoObj, "%d %d", &(novoObjeto->arestas[i][0]), &(novoObjeto->arestas[i][1]));
    }

    novoObjeto->modelMatrix = criaIdentidade4d();

    return novoObjeto;
}
// Altera a modelMatrix de um objeto para redimenciona-lo segundo os parâmetros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ)
{
    objeto->modelMatrix[0][0] += escalaX;
    objeto->modelMatrix[1][1] += escalaY;
    objeto->modelMatrix[2][2] += escalaZ;
}

// Altera a modelMatrix de um objeto para translada-lo segundo os parâmetros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ)
{
    objeto->modelMatrix[0][3] += transX;
    objeto->modelMatrix[1][3] += transY;
    objeto->modelMatrix[2][3] += transZ;
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo informado
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo)
{
    float rad = angulo * M_PI / 180.0; // Convertendo para radianos
    float **matrizRotacaoX = criaMatrizRotacaoX(rad);

    // Multiplicando a matriz de rotação pela matriz de modelo do objeto
    // (Assumindo que a multiplicação é feita da direita para a esquerda)
    multMatriz4d(matrizRotacaoX, objeto->modelMatrix);
    limpaMatriz(matrizRotacaoX, 4);
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo)
{
    float rad = angulo * M_PI / 180.0; // Convertendo para radianos
    float **matrizRotacaoX = criaMatrizRotacaoY(rad);

    // Multiplicando a matriz de rotação pela matriz de modelo do objeto
    // (Assumindo que a multiplicação é feita da direita para a esquerda)
    multMatriz4d(matrizRotacaoX, objeto->modelMatrix);
    limpaMatriz(matrizRotacaoX, 4);
}

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo)
{
    float rad = angulo * M_PI / 180.0; // Convertendo para radianos
    float **matrizRotacaoX = criaMatrizRotacaoZ(rad);

    // Multiplicando a matriz de rotação pela matriz de modelo do objeto
    // (Assumindo que a multiplicação é feita da direita para a esquerda)
    multMatriz4d(matrizRotacaoX, objeto->modelMatrix);
    limpaMatriz(matrizRotacaoX, 4);
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
        printf(" [%d] - (%8.4f, %8.4f, %8.4f)\n", i + 1, objeto->pontos[i][0], objeto->pontos[i][1], objeto->pontos[i][2]);

    printf("Arestas\n");

    for (int i = 0; i < objeto->nArestas; i++)
        printf(" [%d] - (%3d, %3d)\n", i + 1, objeto->arestas[i][0], objeto->arestas[i][1]);
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