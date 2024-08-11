#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Ajusta valores de um matriz 4d para uma matriz identidade
float **criaIdentidade4d()
{
    float **matriz = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++)
    {
        matriz[i] = (float *)calloc(4, sizeof(float));
        matriz[i][i] = 1.0;
    }

    return matriz;
}

// Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%8.4f ", matriz[i][j]);
        printf("\n");
    }
}

// Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto)
{
    float *resultado = (float *)malloc(4 * sizeof(float));

    for (int i = 0; i < 4; i++)
    {
        resultado[i] = 0.0;
        for (int j = 0; j < 4; j++)
            resultado[i] += matriz[i][j] * ponto[j];
    }

    return resultado;
}

// Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB)
{
    float matrizC[4][4], soma;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            soma = 0;
            for (int k = 0; k < 4; k++)
                soma += matrizA[i][k] * matrizB[k][j];
            matrizC[i][j] = soma;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            matrizB[i][j] = matrizC[i][j];
    }
}

float **criaMatrizRotacaoX(float angulo)
{
    float **matriz = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++)
        matriz[i] = calloc(4, sizeof(float));

    float c = cos(angulo);
    float s = sin(angulo);

    matriz[0][0] = matriz[3][3] = 1;
    matriz[1][1] = matriz[2][2] = c;
    matriz[1][2] = sin(-angulo);
    matriz[2][1] = s;

    return matriz;
}

float **criaMatrizRotacaoY(float angulo)
{
    float **matriz = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++)
        matriz[i] = calloc(4, sizeof(float));

    float c = cos(angulo);
    float s = sin(angulo);

    matriz[1][1] = matriz[3][3] = 1;
    matriz[0][0] = matriz[2][2] = c;
    matriz[0][2] = s;
    matriz[2][0] = sin(-angulo);

    return matriz;
}

float **criaMatrizRotacaoZ(float angulo)
{
    float **matriz = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++)
        matriz[i] = calloc(4, sizeof(float));

    float c = cos(angulo);
    float s = sin(angulo);

    matriz[2][2] = matriz[3][3] = 1;
    matriz[0][0] = matriz[1][1] = c;
    matriz[0][1] = sin(-angulo);
    matriz[1][0] = s;

    return matriz;
}

void limpaMatriz(float **matriz, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}