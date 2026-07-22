#include "Engine.h"
#include "Player.h"
#include "Enemy.h" 
#include <fmod.hpp>

#include <iostream>
#include <vector>

using namespace nu;

int main()
{
    // INITIALIZATION
    engine.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);
    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    // test FMOD working on startup
    //FMOD::Sound* sound = nullptr;
    //audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
    //audio->playSound(sound, 0, false, nullptr);

    // create and store all sounds in vector
    std::vector<FMOD::Sound*> sounds;
    FMOD::Sound* sound = nullptr;

    audio->createSound("alert.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("duck-toy.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("error.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);



    // mesh / model
    //Mesh mesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{ -2, -2 }, Vector2{ 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f } };
    Mesh mesh{ { Vector2{ 10, 0 }, Vector2{ 7, -8 }, Vector2{ -7, -8 }, Vector2{ -10, 0 }, Vector2{ -7, 8 }, Vector2 { 7 , 8 }, Vector2 { 10 , 0 } }, Color{ 0.9f, 0.8f, 1.0f } };
    Mesh mesh2{ { Vector2{ 7, -8 }, Vector2{ 4, -13 }, Vector2{ 1, -8 } }, Color{ 1.0f, 0.0f, 0.5f } };
    Mesh mesh3{ { Vector2{ -7, -8 }, Vector2{ -4, -13 }, Vector2{ -1, -8 } }, Color{ 1.0f, 0.0f, 0.5f } };
    Mesh mesh4{ { Vector2{ 3, -1 }, Vector2{ 3, -4 }, Vector2{ 5, -4 }, Vector2{ 5, -1 }, Vector2{ 3, -1 } }, Color{ 0.2f, 0.2f, 0.8f } };
    Mesh mesh5{ { Vector2{ -3, -1 }, Vector2{ -3, -4 }, Vector2{ -5, -4 }, Vector2{ -5, -1 }, Vector2{ -3, -1 } }, Color{ 0.2f, 0.2f, 0.8f } };
    
    Model model{ std::vector<Mesh> { mesh } };
    model.AddMesh(mesh2);
    model.AddMesh(mesh3);
    model.AddMesh(mesh4);
    model.AddMesh(mesh5);

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);
        
    //for (int i = 0; i < 20; i++) {
    //    EnemyDesc enemyDesc;
    //    enemyDesc.name = "Enemy";
    //    enemyDesc.model = model;
    //    enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()), nu::RandomFloat((float)nu::engine.GetRenderer().GetHeight())}, 0.0f, 10.0f };
    //    enemyDesc.speed = 2000.0f;

    //    Enemy* enemy = new Enemy{ enemyDesc };
    //    scene.AddActor(enemy);
    //}

    // Drawing
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

        // Audio Keymapping
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }
        
        // engine
        float dt = engine.GetTime().GetDeltaTime();

        engine.Update();
        scene.Update(dt);
        audio->update();
 
        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        // Drawing Logic
        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) {

            Vector2 position;
            position = engine.GetInput().GetMousePosition();

            if (points.size() > 0) {
                if ((position - points.back()).Length() > 10) {
                    points.push_back(position);
                }
            }
            else {
                points.push_back(position);
            }

        }

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (size_t i = 1; i < points.size(); i++)
        {
            engine.GetRenderer().SetColor(RandomFloat(256), RandomFloat(256), RandomFloat(256));
            engine.GetRenderer().DrawLine(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
        }

        scene.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    }

    // SHUTDOWN
    engine.GetRenderer().Shutdown();
    return 0;
}
