#pragma once

#include <iostream>

#include "box2d/box2d.h"
#include "entity.hpp"

class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact *contact) override {
        //std::cout << m_entity.canJump << std::endl;
        m_entity.canJump++;
    }

    void EndContact(b2Contact *contact) override {
        m_entity.canJump--;
    }

    public:
        MyContactListener(Entity &entity) : m_entity(entity) {};
        Entity &m_entity;
};