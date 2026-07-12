#include "Engine.h"

using namespace nu;

struct Transform {
    Vector2 position;
    float rotation;
    float scale;
};

class Actor {
public: 
    Actor() = default; 
    Actor(const Transform& transform) : m_transform{ transform } {};

    void Update(float dt) {
        m_transform.position += (m_velocity * dt); 
        m_velocity *= 0.987f;

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer) const {
        renderer.SetColor(0.0f, 0.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform; }
    void SetPosition(const Vector2& position) { m_transform.position = position; }
    void SetRotation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.scale = scale; }

    const Vector2& GetVelocity() const { return m_velocity; }
    void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }

protected: 
    Transform m_transform;
    Vector2 m_velocity{0, 0};

};


int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    Input input;
    input.Initialize();
    
    Time time;

    Actor player{ Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f } };

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

        // ADD TO POINTS VECTOR ON CLICK
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
