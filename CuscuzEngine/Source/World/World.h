#pragma once

class Actor;
class Component;

// The world is going to be created as soon as the game starts. All the game state and entities is
// going to be stored in there.
class World
{
    std::vector<std::shared_ptr<Actor>> m_ActiveActors;
    std::vector<std::shared_ptr<Actor>> m_PendingActors;
    bool m_UpdatingActors = false;

public:
    World() = default;
    ~World() = default;

    void Update(float DeltaTime);
    void AddActor(Actor* Actor);
    void RemoveActor(Actor* ActorToRemove);

    size_t GetActorsCount() const { return m_ActiveActors.size(); }

    std::vector<std::shared_ptr<Actor>> GetAllActors() const
    { return m_ActiveActors; }

private:
    void HandleDeadActors();

    void OnActorComponentAdded(const std::shared_ptr<Component>& NewComponent);
};
