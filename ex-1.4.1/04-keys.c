#include <SDL2/SDL.h>
#include <stdbool.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    int x, y;
    SDL_Rect r = { 40, 20, 10, 10 }; 
    SDL_Rect pontos[10];
    int cores[10][3] = {
        {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {255,165,0},
        {0,255,255}, {128,0,128}, {139,69,19}, {0,128,128}, {128,128,0}
    };
    int npontos = 0;

    SDL_Event evt;
    bool estado = 1;
    while (estado) {

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);

        for (int i = 0; i < npontos; i++) {
            SDL_SetRenderDrawColor(ren, cores[i][0], cores[i][1], cores[i][2], 0x00);
            SDL_RenderFillRect(ren, &pontos[i]);
        }

        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:    r.y -= 5; break;
                case SDLK_DOWN:  r.y += 5; break;
                case SDLK_LEFT:  r.x -= 5; break;
                case SDLK_RIGHT: r.x += 5; break;
            }
            if (r.x < 0) r.x = 0;
            if (r.y < 0) r.y = 0;
            if (r.x + r.w > 200) r.x = 200 - r.w;
            if (r.y + r.h > 100) r.y = 100 - r.h;
        }
        else if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (npontos < 10) {
                SDL_GetMouseState(&x, &y);
                pontos[npontos] = (SDL_Rect){ x, y, 10, 10 };
                npontos++;
            }
        }
        else if (evt.type == SDL_WINDOWEVENT_CLOSE){
            estado = 0;
        }
        else if (evt.type == SDL_QUIT) {
            estado = 0;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
