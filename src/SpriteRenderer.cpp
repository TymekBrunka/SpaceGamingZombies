#include <SpriteRenderer.hpp>

static bgl::vec2 sprite_shape[6] = {
    {-0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5},
    {-0.5, 0.5}, {0.5, -0.5},  {0.5, 0.5},
};

void SpriteRenderer::init() {
  capacity = 256;
  sprites.reserve(256);
  glCreateBuffers(1, &vbo);
  glBindBuffer(vbo, GL_ARRAY_BUFFER);
  glBufferStorage(GL_ARRAY_BUFFER, 6 * sizeof(bgl::vec2), sprites.data(), GL_DYNAMIC_DRAW);
}

void SpriteRenderer::cleanup() {
  glDeleteBuffers(1, &vbo);
}
