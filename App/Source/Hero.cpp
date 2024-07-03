#include "Hero.h"

#include "Input.h"
#include "KeyCodes.h"

Hero::Hero(World* world, std::string name, glm::vec2 position) :
Actor(world, name, position)
{}

void Hero::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    glm::vec2 movement(0,0);
    
    if(Input::IsKeyPressed(D))
        movement += glm::vec2(1,0);
    if(Input::IsKeyPressed(A))
        movement += glm::vec2(-1,0);
    if(Input::IsKeyPressed(S))
        movement += glm::vec2(0,1);
    if(Input::IsKeyPressed(W))
        movement += glm::vec2(0,-1);

    movement *= moveSpeed * deltaTime;

    m_Position += movement;
}