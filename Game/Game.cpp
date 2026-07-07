#include "Engine.h"

using namespace nu;

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    Input input;
    input.Initialize();

    //std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++) {
        v.push_back({ RandomFloat(1280), RandomFloat(1024) });
    }
    
    // MAIN LOOP
    bool quit = false;

    while (!quit) {

        // UPDATE
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        // engine
        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);


        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        //Renders Random Points
        for (size_t i = 0; i < v.size(); i++) {
            renderer.SetColor(RandomFloat(), RandomFloat(256), RandomFloat(256));

            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        renderer.SetColor(0.0f, 0.0f, 1.0f);
        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        ////Renders Lines
        //for (int i = 0; i < 500; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawLine(800, 800, 700, 700);
        //}

        ////Renders Squares
        //for (int i = 0; i < 1000; i++) {
        //    renderer.SetColor(RandomFloat(256), RandomFloat(256), RandomFloat(256));
        //    renderer.DrawRect(800, 700, 100, 100);
        //}
        
        renderer.Present();
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}
