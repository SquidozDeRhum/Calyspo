#include <iostream>
#include <vector>
#include <ctime>
#include "./include/raylib.h"
#include "./include/player.hpp"
#include "./include/entity.hpp"

int main() {
    std::srand(std::time(0));
    std::vector<Entity> entities(10);
    for (int i(0); i < entities.size(); i++) {
        entities[i] = Entity(int(std::rand() % 1024 - 512), int(std::rand() % 1024 - 512), 50, 50);
    }
    InitWindow(600, 600, "First release of Calypso");
    Camera2D camera;
    camera = {0};
    camera.offset = (Vector2){300, 300};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;
    Player player(camera);
    SetTargetFPS(60);
    Entity entity(500, 500, 50, 50);
    Entity entity2(500, 550, 50, 50);
    Texture2D grass(LoadTexture("./assets/grass.png"));
    while (!WindowShouldClose()) {
        camera = player.rCamera();
        player.move();
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                for (int i(-1024); i < 1024; i += 32) {
                    for (int p(-1024); p < 1024; p += 32) {
                        DrawTexture(grass, i, p, WHITE);
                    }
                }
                for (int i(0); i < entities.size(); i++) {
                    entities[i].render();
                    player.detectCollision(entities[i]);
                }
                entity.render();
                entity2.render();
                player.detectCollision(entity);
                player.detectCollision(entity2);
                player.render();
            EndMode2D();
            player.statRender();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}