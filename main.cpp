#include "raylib.h"
#include "box2d/box2d.h"

#include "include/entity.hpp"
#include "include/player.hpp"

const int width(400);
const int height(400);

const int framerate(60);

int main() {

    SetTargetFPS(framerate);

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    Player player(world, 200, 200, 20, 20, false);
    Entity ground(world, 200, 390, 200, 20);

    InitWindow(width, height, "Basic window");
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(Color{127, 127, 127, 0});
            player.render();
            player.inputHandling();
            ground.render();
        EndDrawing();
        world.Step(1.0f/framerate, 6, 2);
    }

    CloseWindow();
    return 0;
}