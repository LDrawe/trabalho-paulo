#include <stdlib.h>
#include <algebra.h>
#include <camera.h>

tCamera *criaCamera()
{
    tCamera *camera = (tCamera *)malloc(sizeof(tCamera));

    camera->posicao.x = 0.0;
    camera->posicao.y = 0.0;
    camera->posicao.z = 1.0;

    camera->foco.x = 0.0;
    camera->foco.y = 0.0;
    camera->foco.z = 10.0;

    camera->cima.x = 0.0;
    camera->cima.y = 1.0;
    camera->cima.z = 0.0;

    camera->viewMatrix = criaIdentidade4d();

    Vetor forward = normaliza(subtraiVetor(camera->foco, camera->posicao));
    Vetor right = normaliza(produtoVetorial(forward, camera->cima));
    Vetor up = produtoVetorial(right, forward); // Already normalized

    camera->viewMatrix[0][0] = right.x;
    camera->viewMatrix[0][1] = right.y;
    camera->viewMatrix[0][2] = right.z;
    camera->viewMatrix[0][3] = -produtoEscalar(right, camera->posicao);

    camera->viewMatrix[1][0] = up.x;
    camera->viewMatrix[1][1] = up.y;
    camera->viewMatrix[1][2] = up.z;
    camera->viewMatrix[1][3] = -produtoEscalar(up, camera->posicao);

    camera->viewMatrix[2][0] = -forward.x;
    camera->viewMatrix[2][1] = -forward.y;
    camera->viewMatrix[2][2] = -forward.z;
    camera->viewMatrix[2][3] = produtoEscalar(forward, camera->posicao);

    camera->viewMatrix[3][0] = 0;
    camera->viewMatrix[3][1] = 0;
    camera->viewMatrix[3][2] = 0;
    camera->viewMatrix[3][3] = 1;

    return camera;
}

void desalocaCamera(tCamera *camera)
{
    limpaMatriz(camera->viewMatrix);
}