#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

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

void mover(SDL_Rect* q1, SDL_Rect* q2, SDL_Rect* q3, SDL_Rect* q4, int* vel){
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
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "01.png");
    assert(img != NULL);

    SDL_Rect q1 = { 100, 100, 40, 40 };  
    SDL_Rect q2 = { 200, 100, 40, 40 };    
    SDL_Rect q3 = { 200, 200, 40, 40 };      
    SDL_Rect q4 = { 100, 200, 40, 40 };   

    int vel = 1;
    bool estado = true;
    bool pausado = false;
    bool move = false;

    Uint32 ultimoFrame = SDL_GetTicks();
    Uint32 intervaloAnim = 500;
    Uint32 espera = 100;

    SDL_Event evt;
    while (estado) {
        Uint32 agora = SDL_GetTicks();
        int isevt = AUX_WaitEventTimeout(&evt, &espera);
        if (isevt) {
            if (evt.type == SDL_QUIT) {
                estado = false;
            }
            else if (evt.type == SDL_KEYDOWN) {
                if (evt.key.keysym.sym == SDLK_SPACE)
                    pausado = !pausado;
                else if (evt.key.keysym.sym == SDLK_UP)
                    vel = 2;
            }
            else if (evt.type == SDL_KEYUP) {
                if (evt.key.keysym.sym == SDLK_UP)
                    vel = 1;
            }
        }

        else if (!pausado) {
            mover(&q1, &q2, &q3, &q4, &vel);
            if (agora - ultimoFrame >= intervaloAnim) {
              move = !move;
              ultimoFrame = agora;
            }
            espera = 100;
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_Rect c = move ? (SDL_Rect){100, 0, 100, 80}
                          : (SDL_Rect){0, 0, 100, 80};

        SDL_RenderCopy(ren, img, &c, &q1);
        SDL_RenderCopy(ren, img, &c, &q2);
        SDL_RenderCopy(ren, img, &c, &q3);
        SDL_RenderCopy(ren, img, &c, &q4);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
