#include <iostream>
#include <fstream>
#include <vector>

#include "raylib.h"
#include "box2d/box2d.h"
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

#include "include/entity.hpp"
#include "include/player.hpp"

const int screenWidth(400);
const int screenHeight(400);

const int frameRate(60);

std::ifstream tilemap("../assets/tilemap/calypso.json");
json tilemapJson = json::parse(tilemap);

std::ifstream texturesInfo("../assets/tilemap/sheet.json");
json texturesInfoJson = json::parse(texturesInfo);

std::vector<int> vec = tilemapJson["layers"][1]["data"];

std::map<int, Texture2D> textures;

int height = tilemapJson["layers"][1]["height"];
int width = tilemapJson["layers"][1]["width"];

std::vector<Entity> entities;

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

    for (json::iterator it = texturesInfoJson["tiles"].begin(); it != texturesInfoJson["tiles"].end(); it++) {
        std::string value = it.value()["properties"][0]["value"];
        value = "../assets/textures/" + value;
        char *cvalue = value.data();
        int index = it.value()["id"];
        textures[index + 1] = LoadTexture(cvalue);
    }

    textures[1] = LoadTexture("../assets/textures/character.png");

    Player feur(world, 200, 200, 15, 22, textures[1], false);

    for(int i = 0; i < vec.size(); i++) {
        int x = i % width * 16;
        int y = i / height * 16;
        if (textures.find(vec[i]) != textures.end()) {
            entities.push_back(Entity(world, x, y, 16, 16, textures[vec[i]]));
        }
    }
    
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