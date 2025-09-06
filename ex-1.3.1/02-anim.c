#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
     /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 300, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    const int inicio = 100;
    const int fim = 200;

    // Quatro quadrados
    SDL_Rect q1 = { inicio, inicio, 20, 20 };  
    SDL_Rect q2 = { fim, inicio, 20, 20 };    
    SDL_Rect q3 = { fim, fim, 20, 20 };      
    SDL_Rect q4 = { inicio, fim, 20, 20 };    

    while (1) {
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
        SDL_Delay(100);

        if (q1.x < fim && q1.y == inicio) q1.x += 1;
        else if (q1.x >= fim && q1.y < fim) q1.y += 1;
        else if (q1.y >= fim && q1.x > inicio) q1.x -= 1;
        else if (q1.x <= inicio && q1.y > inicio) q1.y -= 1;

        if (q2.y < fim && q2.x == fim) q2.y += 1;
        else if (q2.y >= fim && q2.x > inicio) q2.x -= 1;
        else if (q2.x <= inicio && q2.y > inicio) q2.y -= 1;
        else if (q2.y <= inicio && q2.x < fim) q2.x += 1;

        if (q3.x > inicio && q3.y == fim) q3.x -= 1;
        else if (q3.x <= inicio && q3.y > inicio) q3.y -= 1;
        else if (q3.y <= inicio && q3.x < fim) q3.x += 1;
        else if (q3.x >= fim && q3.y < fim) q3.y += 1;

        if (q4.y > inicio && q4.x == inicio) q4.y -= 1;
        else if (q4.y <= inicio && q4.x < fim) q4.x += 1;
        else if (q4.x >= fim && q4.y < fim) q4.y += 1;
        else if (q4.y >= fim && q4.x > inicio) q4.x -= 1;
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
