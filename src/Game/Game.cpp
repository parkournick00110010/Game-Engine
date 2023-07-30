#include "Game.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>

Game::Game() {
  isRunning = false;

  registry = std::make_unique<Registry>();

  spdlog::info("Game constructor called!");
}

void
Game::Setup() {
  Entity tank = registry->CreateEntity();

  tank.AddComponent<TransformComponent>(glm::vec2(10.0, 30.0),
                                        glm::vec2(1.0, 1.0), 0);

  tank.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  tank.RemoveComponent<RigidBodyComponent>();
}

void
Game::Update() {
  if (FPS_LIMIT > 0) {
    int timeToWait =
        MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
      SDL_Delay(timeToWait);
    }
  }

  double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

  millisecsPreviousFrame = SDL_GetTicks();
}

void
Game::Render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

Game::~Game() { spdlog::info("Game destractor called!"); }

void
Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::critical("Error initializing SDL.");
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 800;    // displayMode.w;
  windowHeight = 600;   // displayMode.h;

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

  if (!window) {
    spdlog::critical("Error creating SDL Window.");
    return;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    spdlog::critical("Error creating SDL renderer.");
    return;
  }

  if (FULLSCREEN == true) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  }

  isRunning = true;
}

void
Game::Run() {
  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void
Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      break;
    }
  }
}

void
Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}