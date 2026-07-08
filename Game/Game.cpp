#include "Engine.h"

using namespace nu;

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    Input input;
    input.Initialize();

    Time time;

    Vector2 position{ 640.0f, 512.0f };
    float speed = 400.0f;
    std::vector<Vector2> points;
    
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
        time.Tick();

        //prevTicks = ticks;
        //ticks = SDL_GetTicksNS(); // 1,000,000,000 ticks/second
        //float seconds = (float)ticks / 1000'000'000.0f;
        //float dt = (ticks - prevTicks) / 1000'000'000.0f;
        
        //std::cout << seconds << " " << dt << std::endl;
        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";
        //if (input.GetButtonPressed(Input::MouseButton::Left))  std::cout << "button pressed\n";



        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);


        if (input.GetButtonPressed(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }


        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +speed;

        position += (velocity * time.GetDeltaTime());


        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        //Renders Random Points
        for (size_t i = 0; i < points.size(); i++) {
            renderer.SetColor(RandomFloat(), RandomFloat(256), RandomFloat(256));
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // character
        renderer.SetColor(0.0f, 0.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        //points[i] = points[i] + vel;

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
