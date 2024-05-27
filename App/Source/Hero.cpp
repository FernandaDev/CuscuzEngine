#include "Hero.h"

#include "Input.h"
#include "KeyCodes.h"

Hero::Hero(std::shared_ptr<World> World, std::string Name, glm::vec2 Position) :
Actor(World, Name, Position)
{}

void Hero::UpdateActor(float DeltaTime)
{
    Actor::UpdateActor(DeltaTime);

    glm::vec2 movement(0,0);
    
    if(Input::IsKeyPressed(D))
        movement += glm::vec2(1,0);
    if(Input::IsKeyPressed(A))
        movement += glm::vec2(-1,0);
    if(Input::IsKeyPressed(S))
        movement += glm::vec2(0,1);
    if(Input::IsKeyPressed(W))
        movement += glm::vec2(0,-1);

    movement *= moveSpeed * DeltaTime;

    m_Position += movement;
}