#pragma once

class Actor;
class World;
class Application;

class AppGame : public CC_Game
{
public:
    AppGame() = default;
    ~AppGame() override = default;

    void OnGameBegin() override;
    void OnGameEnd() override;
    void UpdateGame(float DeltaTime) override;

private:
    Actor* CreateNewActor(const std::string& Name, int x, int y);

    friend class AppGameLayer;
};
