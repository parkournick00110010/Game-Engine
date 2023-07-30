#include "ECS.h"
#include <algorithm>
#include <spdlog/spdlog.h>

unsigned int IComponent::nextId = 0;

unsigned int
Entity::GetId() const {
  return id;
}

void
System::AddEntityToSystem(Entity entity) {
  entities.push_back(entity);
}

void
System::RemoveEntityFromSystem(Entity entity) {
  entities.erase(
      std::remove_if(entities.begin(), entities.end(),
                     [&entity](Entity other) { return entity == other; }),
      entities.end());
}

std::vector<Entity>
System::GetSystemEntities() const {
  return entities;
}
const Signature &
System::GetComponentSignature() const {
  return componentSignature;
}

Entity
Registry::CreateEntity() {
  unsigned int entityId = numEntities++;

  Entity entity(entityId);

  entity.registry = this;

  entitiesToBeAdded.insert(entity);

  if (entityId >= entityComponentSignatures.size()) {
    entityComponentSignatures.resize(entityId + 1);
  }

  spdlog::info("Entity created with ID: " + std::to_string(entityId));

  return entity;
}

template <typename TComponent>
bool
Registry::HasComponent(Entity entity) const {
  const auto componentId = Component<TComponent>::GetId();
  const auto entityId = entity.GetId();

  return entityComponentSignatures[entityId].test(componentId);
}

void
Registry::AddEntityToSystems(Entity entity) {
  const auto entityId = entity.GetId();

  const auto &entityComponentSignature = entityComponentSignatures[entityId];

  for (auto &system : systems) {
    const auto &systemComponentSignature =
        system.second->GetComponentSignature();

    bool isInterested = (entityComponentSignature & systemComponentSignature) ==
                        systemComponentSignature;

    if (isInterested) {
      system.second->AddEntityToSystem(entity);
    }
  }
}

void
Registry::Update() {
  for (auto entity : entitiesToBeAdded) {
    AddEntityToSystems(entity);
  }
  entitiesToBeAdded.clear();
}