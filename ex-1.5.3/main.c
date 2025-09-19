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

void mover(SDL_Rect* q1, SDL_Rect* q2, SDL_Rect* q3, SDL_Rect* q4, int* vel) {
    // vermelho
    if (q1->x < 200 && q1->y == 100) q1->x += *vel;
    else if (q1->x >= 200 && q1->y < 200) q1->y += *vel;
    else if (q1->y >= 200 && q1->x > 100) q1->x -= *vel;
    else if (q1->x <= 100 && q1->y > 100) q1->y -= *vel;

    // verde
    if (q2->y < 200 && q2->x == 200) q2->y += *vel;
    else if (q2->y >= 200 && q2->x > 100) q2->x -= *vel;
    else if (q2->x <= 100 && q2->y > 100) q2->y -= *vel;
    else if (q2->y <= 100 && q2->x < 200) q2->x += *vel;

    // azul
    if (q3->x > 100 && q3->y == 200) q3->x -= *vel;
    else if (q3->x <= 100 && q3->y > 100) q3->y -= *vel;
    else if (q3->y <= 100 && q3->x < 200) q3->x += *vel;
    else if (q3->x >= 200 && q3->y < 200) q3->y += *vel;

    // amarelo
    if (q4->y > 100 && q4->x == 100) q4->y -= *vel;
    else if (q4->y <= 100 && q4->x < 200) q4->x += *vel;
    else if (q4->x >= 200 && q4->y < 200) q4->y += *vel;
    else if (q4->y >= 200 && q4->x > 100) q4->x -= *vel;
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect q1 = { 100, 100, 20, 20 };  
    SDL_Rect q2 = { 200, 100, 20, 20 };    
    SDL_Rect q3 = { 200, 200, 20, 20 };      
    SDL_Rect q4 = { 100, 200, 20, 20 };    

    Uint32 espera = 100;
    int vel = 1;
    SDL_Event evt;

    bool estado = true;
    bool pausado = false;
    while (estado) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &q1);
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        SDL_RenderFillRect(ren, &q2);
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &q3);
        SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
        SDL_RenderFillRect(ren, &q4);

        SDL_RenderPresent(ren);

        int isevt = AUX_WaitEventTimeout(&evt, &espera);
        if (isevt) {
            if (evt.type == SDL_QUIT) {
                estado = false;
            }
            else if (evt.type == SDL_KEYDOWN) {
              // ao apertar espaço, toda a animaçao é pausada
               if (evt.key.keysym.sym == SDLK_SPACE) {
                    pausado = !pausado;
                }
              // enquanto pressionar a seta para cima, a velocidade da animaçao triplica
              else if (evt.key.keysym.sym == SDLK_UP) {
                    vel = 3;
              }
            }
              else if (evt.type == SDL_KEYUP) {
                // quando soltar a seta para cima, a velocidade da animaçao volta ao normal
                if (evt.key.keysym.sym == SDLK_UP) {
                  vel = 1;
                }
              }
        } 
        else if (pausado == false) {
            mover(&q1, &q2, &q3, &q4, &vel);
            espera = 100;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
