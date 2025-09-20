#include <SDL2/SDL.h>
#include <stdbool.h>


SDL_Rect r, t, p, linha;
bool r_chegou, p_chegou, t_chegou;
int campeao;

void ReiniciarCorrida() {
    r.x = 20;
    t.x = 20;
    SDL_GetMouseState(&p.x, NULL);
    p.x = 20;

    r_chegou = false;
    p_chegou = false;
    t_chegou = false;

    campeao = 0;
}

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    Uint32 antes = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();
    Uint32 d = depois - antes;

    if (d >= *ms) {
        *ms = 0;
    } else {
        *ms -= d;
    }
    return ret;
}

int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Corrida",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       200, 200, SDL_WINDOW_SHOWN
                                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    Uint32 espera = 100;

    r = (SDL_Rect){20, 40, 10, 10};
    t = (SDL_Rect){20, 90, 10, 10};
    p = (SDL_Rect){20, 140, 10, 10};
    linha = (SDL_Rect){190, 0, 2, 200};

    ReiniciarCorrida();

    bool estado = true;
    SDL_Event evt;

    while (estado) {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(ren, &t);

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderDrawRect(ren, &p);

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(ren, &linha);

        SDL_RenderPresent(ren);

        int isevt = AUX_WaitEventTimeout(&evt, &espera);
        if (isevt) {
            if (evt.type == SDL_KEYDOWN && r_chegou == false) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        r.x -= 1;
                        break;
                    case SDLK_RIGHT:
                        r.x += 1;
                        break;
                }
            } else if (evt.type == SDL_MOUSEMOTION && p_chegou == false) {
                p.x = evt.motion.x;
            } else if (evt.type == SDL_WINDOWEVENT_CLOSE || evt.type == SDL_QUIT) {
                estado = false;
            }
        } else if (t_chegou == false) {
            espera = 100;
            t.x += 1;
        }

        if (SDL_HasIntersection(&r, &linha)) {
            r_chegou = true;
            if (t_chegou == false && p_chegou == false) {
                campeao = 1;
            }
        }
        if (SDL_HasIntersection(&t, &linha)) {
            t_chegou = true;
            if (r_chegou == false && p_chegou == false) {
                campeao = 2;
            }
        }
        if (SDL_HasIntersection(&p, &linha)) {
            p_chegou = true;
            if (t_chegou == false && r_chegou == false) {
                campeao = 3;
            }
        }

        if (r_chegou && t_chegou && p_chegou) {
            switch (campeao) {
                case 1: SDL_Log("O teclado ganhou!"); break;
                case 2: SDL_Log("O tempo ganhou!"); break;
                case 3: SDL_Log("O mouse ganhou!"); break;
            }
            ReiniciarCorrida();
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
