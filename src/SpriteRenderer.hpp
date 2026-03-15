#pragma once
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>

struct Sprite {
  bgl::vec2 origin;
  bgl::vec2 size;
  bgl::mat4 transforms;
};

class SpriteRenderer {
  bgl::VBO vbo;
  bgl::VAO vao;
  uint32_t capacity; // variable to backtrack sprites vector in order to detect whether to create a new vbo
public:
  std::vector<Sprite> sprites;

  SpriteRenderer() = default;
  ~SpriteRenderer() = default;
  void init();
  void cleanup();
};
