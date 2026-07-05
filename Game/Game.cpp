#include "Engine.h"
#include "SDL3/SDL.h"
#include <iostream>


int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        //EX: drawing lines with points
        //renderer.DrawPoint(50, i + 50);
        //renderer.DrawPoint(125, i + 200);

        //Renders Lines
        for (int i = 0; i < 500; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(800, 800, 700, 700);
            renderer.DrawLine(1250, 900, 900, 900);
            renderer.DrawLine(1530, 500, 1400, 1400);
            renderer.DrawLine(1700, 200, 1000, 1000);
            renderer.DrawLine(800, 100, 925, 830);
            renderer.DrawLine(1500, 200, 1000, 75);
            renderer.DrawLine(100, 50, 25, 700);
            renderer.DrawLine(200, 350, 425, 700);
            renderer.DrawLine(400, 700, 375, 800);
            renderer.DrawLine(425, 500, 600, 125);
        }

        //Renders Random Points
        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1920, rand() % 1024);
        }

        //Renders Squares
        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawRect(800, 700, 100, 100);
            renderer.DrawRect(300, 300, 75, 75);
            renderer.DrawRect(400, 600, 125, 125);
        }
        
        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}
