#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* Window{SDL_CreateWindow(
      "Hello Window", 800, 300, 0
    )};

    bool IsRunning = true;
    SDL_Event Event;
    while (IsRunning) {
      while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_EVENT_QUIT) {
          IsRunning = false;
        }
      }
    }

    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}
