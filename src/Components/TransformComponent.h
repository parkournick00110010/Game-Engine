#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent {
  glm::vec2 position;
  glm::vec2 scale;
  double rotation;

  TransformComponent (
      gml::vec2 position = gml::vec2(0,0),
      gml::vec2 scale = gml::vec2(1,1),
      double rotation
    ) 
  {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
  }
}

#endif