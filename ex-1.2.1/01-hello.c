#include <SDL2/SDL.h>
 
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 300, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
 
    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0xFF);
    SDL_RenderDrawLine( ren, 50, 20, 359, 20 );
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0xFF);
    SDL_Rect j = { 50,20, 10,260 };
    SDL_RenderFillRect(ren, &j);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_Rect i = { 50,270, 300,10 };
    SDL_RenderDrawLine( ren, 50, 280, 359, 280 );
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
    SDL_Rect k = { 350,20, 10,260 };
    SDL_RenderFillRect(ren, &k);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
    SDL_Rect n = { 80,40, 100, 220};
    SDL_RenderFillRect(ren, &n);
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0xFF);
    SDL_Rect g = { 220, 40, 100, 220};
    SDL_RenderFillRect(ren, &g);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
 
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
