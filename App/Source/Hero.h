#pragma once
#include "World/Actor.h"

class Hero : public Actor
{
    float moveSpeed = 400;
    float rotateSpeed = 40;
    
public:
    Hero(World* world, std::string name, glm::vec2 position);
    ~Hero() override = default;
    
    void UpdateActor(float deltaTime) override;
};
