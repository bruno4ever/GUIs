#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
 
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
 
    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);


    filledCircleRGBA(ren, 180, 200, 50, 0, 0, 0, 255);
    filledCircleRGBA(ren, 420, 200, 50, 0, 0, 0, 255);

    roundedBoxRGBA(ren, 210, 150, 390, 250, 20, 0, 0, 255, 255);

    filledCircleRGBA(ren, 420, 200, 20, 255, 255, 255, 255);
    filledCircleRGBA(ren, 180, 200, 20, 255, 255, 255, 255);

    Sint16 vx[3] = {300, 350, 250};
    Sint16 vy[3] = {200, 250, 250};
    filledPolygonRGBA(ren, vx, vy, 3, 255, 255, 255, 255);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
 
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
