#include "./include/raylib.h"

class Player {
    public:
        Player(Camera2D & cam);
        void keyhandling();
        void move();
        void render();
        void statRender();
        void detectCollision(Rectangle entity);
        Camera2D rCamera();
        Rectangle rCollision();
    private:
        Texture2D perso;
        float m_x, m_y;
        Vector2 velocity;
        bool up, down, right, left, debug;
        Camera2D camera;
        Rectangle collision;
};