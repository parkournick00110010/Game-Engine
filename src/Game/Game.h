#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

const int FPS_LIMIT = 60; // 0 to unlimited
const int MILLISECS_PER_FRAME = 1000 / FPS_LIMIT;
const bool FULLSCREEN = false;

class Game {
  private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int millisecsPreviousFrame = 0;

  public:
    Game();
    ~Game();

    void Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void Setup();

    int windowWidth;
    int windowHeight;
};

#endif