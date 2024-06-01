#pragma once
#include "World/Actor.h"

class Hero : public Actor
{
    float moveSpeed = 400;
    float rotateSpeed = 40;
    
public:
    Hero(World* World, std::string Name, glm::vec2 Position);
    ~Hero() override = default;
    
    void UpdateActor(float DeltaTime) override;
};
