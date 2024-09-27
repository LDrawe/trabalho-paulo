#include "algebra.h"
#include "camera.h"
#include "objeto.h"
#include "controls.h"

// Função para processar eventos de teclado
void processaInput(tCamera *camera, tObjeto3d *cubo)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    float speed = 0.1f;

    if (state[SDL_SCANCODE_R])
        resetaObjeto(cubo);

    if (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        moveCameraForward(camera, speed);

    if (state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        camera->posicao = subtraiVetor(camera->posicao, escalaVetor(normaliza(subtraiVetor(camera->foco, camera->posicao)), speed));

    if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
    {
        Vetor right = normaliza(produtoVetorial(normaliza(subtraiVetor(camera->foco, camera->posicao)), camera->cima));
        camera->posicao = somaVetor(camera->posicao, escalaVetor(right, speed));
    }

    if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
    {
        Vetor right = normaliza(produtoVetorial(normaliza(subtraiVetor(camera->foco, camera->posicao)), camera->cima));
        camera->posicao = subtraiVetor(camera->posicao, escalaVetor(right, speed));
    }

    if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, 0.0f, 0.0f, -0.1f);

    if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, 0.0f, 0.0f, 0.1f);

    if (state[SDL_SCANCODE_KP_PLUS])
        escalaObjeto(cubo, 0.02f);

    if (state[SDL_SCANCODE_KP_MINUS])
        escalaObjeto(cubo, -0.02f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_UP])
        rotacionaObjeto(cubo, 'X', 1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        rotacionaObjeto(cubo, 'X', -1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        rotacionaObjeto(cubo, 'Y', 1.0f);

    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        rotacionaObjeto(cubo, 'Y', -1.0f);

    if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_RIGHT])
        rotacionaObjeto(cubo, 'Z', 1.0f);

    if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_LEFT])
        rotacionaObjeto(cubo, 'Z', -1.0f);

    defineCamera(camera);
}

void moveCameraForward(tCamera *camera, float speed) {
    Vetor forward = normaliza(subtraiVetor(camera->foco, camera->posicao));
    camera->posicao = somaVetor(camera->posicao, escalaVetor(forward, speed));
    camera->foco = somaVetor(camera->foco, escalaVetor(forward, speed));
}