#include <iostream>
#include "./include/box2d/box2d.h"
#include "./include/raylib.h"

int main() {
    const int screenWidth(400);
    const int screenHeight(400);

    const int frameRate(60);

    const float RATIO(32.0f);

    bool debug = false;

    SetTargetFPS(frameRate);

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Red Box

    Vector2 pos{0.0f, 20.0f};
    Rectangle collision{pos.x - 1, pos.y - 1, 21.0f, 21.0f};

    b2BodyDef bd;
    b2Body *body;
    b2PolygonShape shape;
    b2FixtureDef fd;
    b2Vec2 velocity;

    bd.position.Set(pos.x / RATIO + 10 / RATIO, pos.y / RATIO + 10 / RATIO);
    bd.type = b2_dynamicBody;
    bd.awake = true;
    bd.fixedRotation = true;

    shape.SetAsBox(10.0f / RATIO, 10.0f / RATIO);

    fd.shape = &shape;
    fd.friction = 1.0f;
    fd.density = 1.0f;

    body = world.CreateBody(&bd);

    body->CreateFixture(&fd);

    body->SetFixedRotation(true);

    // Ground

    b2Body *ground;

    Vector2 gpos{0.0f, 380.0f};
    Rectangle gcollision{gpos.x - 1, gpos.y - 1, 401.0f, 21.0f};

    bd.position.Set(gpos.x / RATIO + 200 / RATIO, gpos.y / RATIO + 10 / RATIO);
    bd.type = b2_staticBody;
    bd.awake = true;
    bd.fixedRotation = true;

    shape.SetAsBox(200.0f / RATIO, 10.0f / RATIO);

    fd.shape = &shape;

    ground = world.CreateBody(&bd);

    ground->CreateFixture(&fd);

    InitWindow(screenWidth, screenHeight, "Basic window");
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(Color{127, 127, 127, 0});
            DrawRectangleV(pos, Vector2{20, 20}, RED);
            DrawRectangleV(gpos, Vector2{400, 20}, RED);

            if (debug) {
                std::cout << collision.y << std::endl;
                std::cout << pos.y << std::endl;
                DrawRectangleRec(GetCollisionRec(collision, gcollision), Color{0, 0, 40, 110});
                DrawRectangleLinesEx(collision, 1.0f, Color{255, 255, 255, 255});
            }

        EndDrawing();
        world.Step(1.0f/frameRate, 6, 2);
        pos.y = body->GetPosition().y * RATIO -9.25f;
        pos.x = body->GetPosition().x * RATIO - 10.0f;
        collision.x = pos.x;
        collision.y = pos.y;
        if (IsKeyDown(KEY_A)) {
            velocity = body->GetLinearVelocity();
            velocity.x = -8.0f;
            body->SetLinearVelocity(velocity);
        }
        if (IsKeyDown(KEY_D)) {
            velocity = body->GetLinearVelocity();
            velocity.x = 8.0f;
            body->SetLinearVelocity(velocity);
        }
        if (IsKeyPressed(KEY_SPACE) && CheckCollisionRecs(collision, gcollision)) {
            velocity = b2Vec2(0.0f, -30.0f);
            body->ApplyForceToCenter(velocity, true);
        }
        if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && CheckCollisionRecs(collision, gcollision)) {
            velocity = body->GetLinearVelocity();
            velocity.x = 0.0f;
            body->SetLinearVelocity(velocity);
        }   
        if (IsKeyPressed(KEY_Y)) {
            if (debug) {
                debug = false;
            }
            else {
                debug = true;
            }
        }
    }

    CloseWindow();

    return 0;
}