#include <iostream>
#include <fstream>
#include <vector>

#include "raylib.h"
#include "box2d/box2d.h"
#include "include/nlohmann/json.hpp"

#include "include/collision.hpp"

using json = nlohmann::json;

#include "include/entity.hpp"
#include "include/player.hpp"
#include "include/loading.hpp"

const int screenWidth(400);
const int screenHeight(400);

const int frameRate(60);

int main() {

    SetTargetFPS(frameRate);

    b2Vec2 gravity(0.0f, 19.6f);
    b2World world(gravity);

    InitWindow(screenWidth, screenHeight, "Json level creation");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 200, 200 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    Texture2D texture = LoadTexture("./assets/textures/character.png");

    Player feur(world, 200, 200, 15, 22, texture, false);

    std::vector<Entity> entities = levelLoading("test_level", world);

    MyContactListener contactListener(feur);
    
    world.SetContactListener(&contactListener);

    while(!WindowShouldClose()) {
        feur.positionProcess();
        camera.target = feur.getRaylibPos();
        BeginDrawing();
            ClearBackground(Color{0, 100, 150, 0});
            BeginMode2D(camera);
                feur.render();
                for (int i = 0; i < entities.size(); i++) {
                    entities[i].render();
                }
            EndMode2D();
            DrawFPS(10, 10);
        EndDrawing();
        world.Step(1.0f/frameRate, 6, 2);
    }
    CloseWindow();
    return 0;
}