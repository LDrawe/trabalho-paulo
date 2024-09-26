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

tProj* criaProjecao(int tipo, float left, float right, float top, float bottom, float near, float far) {
    tProj *proj = (tProj*) malloc(sizeof(tProj));
    
    proj->tipo = tipo;
    proj->left = left;
    proj->right = right;
    proj->top = top;
    proj->bottom = bottom;
    proj->near = near;
    proj->far = far;

    proj->projectionMatrix = (float**) malloc(4 * sizeof(float*));
    for (int i = 0; i < 4; i++) {
        proj->projectionMatrix[i] = (float*) malloc(4 * sizeof(float));
    }

    return proj;
}

void defineProjecao(tProj *proj) {
    if (proj == NULL || proj->projectionMatrix == NULL) return;

    float left = proj->left;
    float right = proj->right;
    float top = proj->top;
    float bottom = proj->bottom;
    float near = proj->near;
    float far = proj->far;

    proj->projectionMatrix[0][0] = 2.0f / (right - left);
    proj->projectionMatrix[0][1] = 0.0f;
    proj->projectionMatrix[0][2] = 0.0f;
    proj->projectionMatrix[0][3] = -(right + left) / (right - left);

    proj->projectionMatrix[1][0] = 0.0f;
    proj->projectionMatrix[1][1] = 2.0f / (top - bottom);
    proj->projectionMatrix[1][2] = 0.0f;
    proj->projectionMatrix[1][3] = -(top + bottom) / (top - bottom);

    proj->projectionMatrix[2][0] = 0.0f;
    proj->projectionMatrix[2][1] = 0.0f;
    proj->projectionMatrix[2][2] = -2.0f / (far - near);
    proj->projectionMatrix[2][3] = -(far + near) / (far - near);

    proj->projectionMatrix[3][0] = 0.0f;
    proj->projectionMatrix[3][1] = 0.0f;
    proj->projectionMatrix[3][2] = 0.0f;
    proj->projectionMatrix[3][3] = 1.0f;
}

void desalocaCamera(tCamera *camera)
{
    limpaMatriz(camera->viewMatrix);
    free(camera);
}