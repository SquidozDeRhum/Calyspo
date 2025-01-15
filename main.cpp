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
#include "include/const.hpp"

int main() {

    SetTargetFPS(FRAMERATE);

    b2Vec2 gravity(0.0f, 19.6f);
    b2World world(gravity);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TEST_LEVEL);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ PLAYER_X, PLAYER_Y };
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = CAMERA_ZOOM;

    Texture2D texture = LoadTexture(ASSETS_FOLDER TEXTURES_FOLDER CHARACTER_TEXTURE);

    Player player(world, PLAYER_X, PLAYER_Y, 15, 22, texture, false);

    std::vector<Entity> entities = levelLoading(TEST_LEVEL, world);

    MyContactListener contactListener(player);
    
    world.SetContactListener(&contactListener);

    while(!WindowShouldClose()) {
        player.positionProcess();
        camera.target = player.getRaylibPos();
        BeginDrawing();
            ClearBackground(Color(BACKGROUND_COLOR));
            BeginMode2D(camera);
                player.render();
                for (int i = 0; i < entities.size(); i++) {
                    entities[i].render();
                }
            EndMode2D();
        EndDrawing();
        world.Step(1.0f/FRAMERATE, 6, 2);
    }
    CloseWindow();
    return 0;
}