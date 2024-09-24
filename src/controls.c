#include "objeto.h"

// Função para processar eventos de teclado
void processaInput(tObjeto3d *cubo)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_R])
        resetaObjeto(cubo);

    if (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, 0.0f, -0.1f, 0.0f);

    if (state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, 0.0f, 0.1f, 0.0f);

    if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, 0.1f, 0.0f, 0.0f);

    if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_LALT])
        transladaObjeto(cubo, -0.1f, 0.0f, 0.0f);

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
}