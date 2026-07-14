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

    //std::vector<Vector2> points{ { -3, 3 }, { 3, 3 } };
    Mesh mesh{ { Vector2{ -3, 3 }, Vector2{ 3, 3 }, Vector2{ 0, 0 } }, Color{0.0f, 0.0f, 1.0f} };

    Actor player{ Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh> { mesh } };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 800.0f;

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

        // Drawing (with mouse) Logic
        if (input.GetButtonDown(Input::MouseButton::Left)) {

            Vector2 position;
            position = input.GetMousePosition();

            if (points.size() > 0) {
                if ((position - points.back()).Length() > 10) {
                    points.push_back(position);
                }
            }
            else {
                points.push_back(position);
            }

        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());
        //position.x = Wrap(0.0f, 1280.0f, position.x);
        //position.y = Wrap(0.0f, 1024.0f, position.y);

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (size_t i = 1; i < points.size(); i++)
        {
            renderer.SetColor(RandomFloat(256), RandomFloat(256), RandomFloat(256));
            renderer.DrawLine(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
        }

        // Renders Box
        //for (size_t i = 0; i < points.size(); i++) {
        //    renderer.SetColor(RandomFloat(256), RandomFloat(256), RandomFloat(256));
        //    renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        //}

        // character
        player.Draw(renderer);
        //renderer.SetColor(0.0f, 0.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
        
        //points[i] = points[i] + vel;
        // Renders Random Points
        //for (int i = 0; i < 300; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(256), RandomFloat(256));
        //    renderer.DrawPoint(RandomFloat(1920), RandomFloat(1024));
        //}

        //Renders Random Lines
        //for (int i = 0; i < 500; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawLine(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
        //}

        //Renders Random Squares
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
