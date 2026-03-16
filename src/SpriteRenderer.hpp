#pragma once
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include <glm/mat4x4.hpp>

struct Sprite {
  bgl::vec4 tex_cords;
  bgl::vec2 size;
  glm::mat4 transforms;
};

class SpriteRenderer {
  static bgl::VBO sprite_shape_;
  bgl::Program program;
  bgl::VBO vbo;
  bgl::VAO vao;
  bgl::Location transforms_location;
  bgl::Location tex_cords_location;
  bgl::Location sprite_size_location;
  uint32_t capacity; // variable to backtrack sprites vector in order to detect whether to create a new vbo
  uint32_t length; // variable to backtrack sprites vector in order to determine which part has been updated

  void reset_vao();
public:
  std::vector<Sprite> sprites;

  SpriteRenderer() = default;
  ~SpriteRenderer() = default;
  void rebuildVBO();
  void render();

  void init(bgl::Program program);
  void cleanup();
};
