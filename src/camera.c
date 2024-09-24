#include <stdlib.h>
#include <algebra.h>
#include <camera.h>

tCamera *criaCamera()
{
    tCamera *camera = (tCamera *)malloc(sizeof(tCamera));

    camera->viewMatrix = criaIdentidade4d();
    camera->posicao.x = 0.0;
    camera->posicao.y = 0.0;
    camera->posicao.z = 1.0;

    camera->foco.x = 0.0;
    camera->foco.y = 0.0;
    camera->foco.z = 10.0;

    camera->cima.x = 0.0;
    camera->cima.y = 1.0;
    camera->cima.z = 0.0;

    return camera;
}

void desalocaCamera(tCamera* camera) {
    limpaMatriz(camera->viewMatrix);
}