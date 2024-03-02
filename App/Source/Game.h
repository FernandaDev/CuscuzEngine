#pragma once

class Actor;
class World;
class Application;

class Game
{
    bool m_GameIsRunning;
    std::shared_ptr<World> m_World;
    Application* m_App;

    bool added = false;
    
    friend class AppImGuiLayer;
    
public:
    Game(Application* App);
    ~Game();
    
    void StartGame();
    void UpdateGame(float DeltaTime);
    void ShutdownGame();

    bool IsRunning() const { return m_GameIsRunning; }

private:
    Actor* CreateNewActor(const std::string& Name, int x, int y) const;
};
