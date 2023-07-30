#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <spdlog/spdlog.h>

class MovementSystem : public System {
public:
  MovementSystem() {
    RequireComponent<TransformComponent>();
    RequireComponent<RigidBodyComponent>();
  }
  ~MovementSystem() = default;

  void Update(double deltaTime) {
    for (auto entity : GetSystemEntities()) {
      TransformComponent &transform = entity.GetComponent<TransformComponent>();
      const RigidBodyComponent rigidbody =
          entity.GetComponent<RigidBodyComponent>();

      transform.position.x += rigidbody.velocity.x * deltaTime;
      transform.position.y += rigidbody.velocity.y * deltaTime;

      spdlog::info("entity id: " + std::to_string(entity.GetId()) +
                   " position is now: " + std::to_string(transform.position.x) +
                   ", " + std::to_string(transform.position.y));
    }
  }
};

#endif