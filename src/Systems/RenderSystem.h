#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

class RenderSystem : public System {
public:
  RenderSystem() {
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
  }
  ~RenderSystem() = default;

  void Update(SDL_Renderer *renderer) {
    for (auto entity : GetSystemEntities()) {
      const auto transform = entity.GetComponent<TransformComponent>();
      auto sprite = entity.GetComponent<SpriteComponent>();

      SDL_Rect objRect = {static_cast<int>(transform.position.x),
                          static_cast<int>(transform.position.y), sprite.width,
                          sprite.height};

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &objRect);
    }
  }
};

#endif