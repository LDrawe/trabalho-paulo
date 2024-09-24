#include <algebra.h>

#ifndef _tCam
#define _tCam
typedef struct tCam
{
    Vetor posicao;
    Vetor foco;
    Vetor cima;
    float **viewMatrix;
} tCamera;
#endif

tCamera *criaCamera();

void desalocaCamera(tCamera* camera);