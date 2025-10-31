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
    ESPERANDO_CLIQUE,
    CONTANDO_CLIQUES
} Estado;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Múltiplos Cliques", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bool rodando = true;
    SDL_Event evt;
    Estado estado = ESPERANDO_CLIQUE;

    int n = 0;
    Uint32 espera = -1;
    int x_ref = 0, y_ref = 0;
    
    while (rodando) {

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        int isevt = AUX_WaitEventTimeout(&evt, &espera);
        switch (estado) {
        case ESPERANDO_CLIQUE:
            if (evt.type == SDL_QUIT) {
                rodando = false;
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                n = 1;
                x_ref = evt.button.x;
                y_ref = evt.button.y;
                espera = 250;
                estado = CONTANDO_CLIQUES;
                
            }
            break;

        case CONTANDO_CLIQUES:
            if (isevt) {
                if (evt.type == SDL_QUIT) {
                    rodando = false;
                }
                else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                    if (evt.button.x == x_ref && evt.button.y == y_ref) {
                        n++;
                        espera = 250;
                    } else {
                        n = 0;
                        estado = ESPERANDO_CLIQUE;
                    }
                }
            }
            else if (n > 1) { // checar se realmente foram multiplos cliques, nao apenas um 
                SDL_Event userEvent;
                SDL_memset(&userEvent, 0, sizeof(userEvent));
                userEvent.type = SDL_USEREVENT;
                userEvent.user.code = n;
                SDL_PushEvent(&userEvent);
                n = 0;
                estado = ESPERANDO_CLIQUE;
            }
            else {
                n = 0;
                estado = ESPERANDO_CLIQUE;
            }
        break;
        }
        if (evt.type == SDL_USEREVENT) {
            printf("Múltiplos cliques detectados: %d vezes!\n", evt.user.code);
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}
