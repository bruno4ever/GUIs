#include <SDL2/SDL.h>
#include <stdbool.h>
 
int main (int argc, char* args[])
{
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
}
