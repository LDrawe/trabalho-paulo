#include <stdio.h>
#include <stdlib.h>
// Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                novaMatriz[i][j] = 1.0;
            else
                novaMatriz[i][j] = 0.0;
        }
    }
}

// Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%8.4f ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto)
{
    float *resultado;
    int i, j;

    resultado = (float *)malloc(4 * sizeof(float));

    for (int i = 0; i < 4; i++)
    {
        resultado[i] = 0.0;
        for (int j = 0; j < 4; j++)
        {
            resultado[i] += matriz[i][j] * ponto[j];
        }
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
        {
            matrizB[i][j] = matrizC[i][j];
        }
    }
}
