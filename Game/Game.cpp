#include "../Engine/Engine.h"
#include "SDL3/SDL.h"
#include <iostream>

//#define PS5 // Pre-processor Operations
//#ifdef PS5
//#define TEXT "PS5\n"
//#else 
//#define TEXT "XBOX\n"
//#endif
//#define TEXT "hello!\n"
//#define MAX(a, b) ((a > b) ? a : b)

int main()
{
    // Library Func.
    //fnEngine();
    // Macros Ex.
    //std::cout << TEXT;// "Hello World!\n";
    //std::cout << MAX(5, 10);
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        //                               r, g, b, alpha (transparency)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        //SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255); // Set render draw color to green
        SDL_RenderClear(renderer); // Clear the renderer

        SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255); // Set render draw color to green
        SDL_RenderPoint(renderer, rand() % 1280, rand() % 1024);

        SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255); // Set render draw color to green
        SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set render draw color to white
        SDL_RenderDebugText(renderer, 10, 10, "Hello World!");

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
