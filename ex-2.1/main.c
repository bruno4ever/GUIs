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

    bool temQuadrado = false;
    SDL_Rect q = {40, 40, 80, 80};
    SDL_Color cor = {0, 200, 255, 255};
    
    while (rodando) {

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        int isevt = AUX_WaitEventTimeout(&evt, &espera);

        if (temQuadrado) SDL_SetRenderDrawColor(ren, cor.r, cor.g, cor.b, 255); SDL_RenderFillRect(ren, &q);
        
        switch (estado) {
        case ESPERANDO_CLIQUE:
            if (evt.type == SDL_QUIT) {
                rodando = false;
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                n = 1;
                x_ref = evt.button.x;
                y_ref = evt.button.y;
                if (!temQuadrado) q = (SDL_Rect) {x_ref, y_ref, 80, 80}; temQuadrado = true;
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
            int count = evt.user.code;
            switch (count) {
                case 2: // muda cor
                    if (temQuadrado)
                        cor = (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255};
                    break;

                case 3: // aumenta tamanho
                    if (temQuadrado) {
                        q.w += 20;
                        q.h += 20;
                        q.x -= 10;
                        q.y -= 10;
                    }
                    break;

                case 4: // diminui tamanho
                    if (temQuadrado && q.w > 40) {
                        q.w -= 20;
                        q.h -= 20;
                        q.x += 10;
                        q.y += 10;
                    }
                    break;

                case 5: // remove
                    temQuadrado = false;
                    break;


            break;
            }
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}
