#include <SDL2/SDL.h>
#include <stdbool.h>
 
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
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    /* EXECUÇÃO */
    int x;
    int y;
    Uint32 espera = 100;
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Rect t = { 80,20, 10,10 };
    SDL_GetMouseState( &x, &y);
    SDL_Rect p = { x, y, 10,10};
    bool estado = 1;
    SDL_Event evt;
    while (estado) {
        SDL_Event evt;
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(ren, &t);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderDrawRect(ren, &p);
        SDL_RenderPresent(ren);
        int isevt = AUX_WaitEventTimeout(&evt, &espera);
        if (isevt) {

          if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 1;
                    break;
                case SDLK_DOWN:
                    r.y += 1;
                    break;
                case SDLK_LEFT:
                    r.x -= 1;
                    break;
                case SDLK_RIGHT:
                    r.x += 1;
                    break;
            }
         }
        else if (evt.type == SDL_MOUSEMOTION) {
           SDL_GetMouseState( &x, &y);
           p.x = x;
           p.y = y; 
        }
        else if (evt.type == SDL_WINDOWEVENT_CLOSE){
           estado = 0;
           }
        else if (evt.type == SDL_QUIT) {
           estado = 0;
          }
     }
     else {
       espera = 100;
       t.x += 1;
     }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
