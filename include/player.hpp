#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "./raylib.h"
#include "./entity.hpp"
#include "vector"

class Player {
    public:
        Player(Camera2D & cam);
        void keyhandling();
        void move();
        void render();
        void statRender();
        void detectCollision(Entity entity);
        Camera2D rCamera();
        Rectangle rCollision();
    private:
        Texture2D perso;
        Vector2 velocity, one, four, center;
        bool up, down, right, left, debug, check;
        Camera2D camera;
        Rectangle collision;
};

#endif // PLAYER_HPP