#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    Uint32 antes = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();
    Uint32 d = depois - antes;
  
    if (d >= *ms)
        *ms = 0;
    else
        *ms -= d;

    return ret;
}

typedef enum { 
  PARADO, 
  PRESSIONADO, 
  ARRASTANDO 
} Estado;

bool dentroQuadrado(SDL_Rect r, int x, int y) {
    return (x >= r.x && x <= r.x + r.w &&
            y >= r.y && y <= r.y + r.h);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Clicar e arrastar um quadrado - Ex 2.2",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect quadrado = {300, 200, 80, 80};
    int originalX = quadrado.x, originalY = quadrado.y;
    int deslocamentoX = 0, deslocamentoY = 0;
    Estado estado = PARADO;
    bool rodando = true;

    SDL_Event evt;
    Uint32 espera = 100;

    while (rodando) {
        espera = 100;
        if (AUX_WaitEventTimeout(&evt, &espera)) {
            switch (evt.type) {

                case SDL_QUIT:
                    rodando = false;
                    break;

                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE) {
                        if (estado == PRESSIONADO || estado == ARRASTANDO) {
                            quadrado.x = originalX;
                            quadrado.y = originalY;
                            estado = PARADO;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (evt.button.button == SDL_BUTTON_LEFT) {
                        int mx = evt.button.x;
                        int my = evt.button.y;
                        if (dentroQuadrado(quadrado, mx, my) && estado == PARADO) {
                            estado = PRESSIONADO;
                            originalX = quadrado.x;
                            originalY = quadrado.y;
                            deslocamentoX = mx - quadrado.x;
                            deslocamentoY = my - quadrado.y;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (evt.button.button == SDL_BUTTON_LEFT) {
                        if (estado == PRESSIONADO) {
                            estado = PARADO;
                        } else if (estado == ARRASTANDO) {
                            originalX = quadrado.x;
                            originalY = quadrado.y;
                            estado = PARADO;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (estado == PRESSIONADO) {
                        estado = ARRASTANDO;
                    }
                    if (estado == ARRASTANDO) {
                        int mx = evt.motion.x;
                        int my = evt.motion.y;
                        quadrado.x = mx - deslocamentoX;
                        quadrado.y = my - deslocamentoY;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        if (estado == ARRASTANDO)
            SDL_SetRenderDrawColor(ren, 0, 180, 255, 255);
        else
            SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);

        SDL_RenderFillRect(ren, &quadrado);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
