#include "bettergl/Debugging.hpp"
#include <SpriteRenderer.hpp>
#include <iostream>

bgl::VBO SpriteRenderer::sprite_shape_ = 0;

static const bgl::vec4 sprite_shape[6] = {
    {-0.5, 0.5, 0.0, 1.0}, {-0.5, -0.5, 0.0, 0.0}, {0.5, -0.5, 1.0, 0.0},
    {-0.5, 0.5, 0.0, 1.0}, {0.5, -0.5, 1.0, 0.0},  {0.5, 0.5, 1.0, 1.0},
};

void SpriteRenderer::init(bgl::Program program) {
  this->program = program;
  capacity = 256;
  sprites.reserve(256);
  glCreateBuffers(1, &sprite_shape_);
  glBindBuffer(GL_ARRAY_BUFFER, sprite_shape_);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(bgl::vec4), sprite_shape,
               GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  const bgl::Location shape_pos_location =
      glGetAttribLocation(program, "shape_pos");
  const bgl::Location shape_tex_pos_location =
      glGetAttribLocation(program, "shape_tex_pos");

  glEnableVertexAttribArray(shape_pos_location);
  glVertexAttribPointer(shape_pos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(bgl::vec4), (void *)(0 * sizeof(bgl::vec2)));

  glEnableVertexAttribArray(shape_tex_pos_location);
  glVertexAttribPointer(shape_tex_pos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(bgl::vec4), (void *)(1 * sizeof(bgl::vec2)));

  tex_cords_location = glGetAttribLocation(program, "tex_cords");
  sprite_size_location = glGetAttribLocation(program, "sprite_size");
  transforms_location = glGetAttribLocation(program, "transforms");

  glCreateBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * sprites.capacity(),
               sprites.data(), GL_DYNAMIC_DRAW);

  reset_vao();
}

void SpriteRenderer::reset_vao() {
  int pos1 = transforms_location + 0;
  int pos2 = transforms_location + 1;
  int pos3 = transforms_location + 2;
  int pos4 = transforms_location + 3;

  glEnableVertexAttribArray(tex_cords_location);
  glVertexAttribPointer(tex_cords_location, 4, GL_FLOAT, GL_FALSE,
                        sizeof(Sprite), (void *)offsetof(Sprite, tex_cords));
  glVertexAttribDivisor(tex_cords_location, 1);

  glEnableVertexAttribArray(sprite_size_location);
  glVertexAttribPointer(sprite_size_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(Sprite), (void *)offsetof(Sprite, size));
  glVertexAttribDivisor(sprite_size_location, 1);

  glEnableVertexAttribArray(pos1);
  glEnableVertexAttribArray(pos2);
  glEnableVertexAttribArray(pos3);
  glEnableVertexAttribArray(pos4);
  glVertexAttribPointer(
      pos1, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite),
      (void *)(offsetof(Sprite, transforms) + (0 * sizeof(GLfloat))));
  glVertexAttribPointer(
      pos2, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite),
      (void *)(offsetof(Sprite, transforms) + (4 * sizeof(GLfloat))));
  glVertexAttribPointer(
      pos3, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite),
      (void *)(offsetof(Sprite, transforms) + (8 * sizeof(GLfloat))));
  glVertexAttribPointer(
      pos4, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite),
      (void *)(offsetof(Sprite, transforms) + (12 * sizeof(GLfloat))));
  glVertexAttribDivisor(pos1, 1);
  glVertexAttribDivisor(pos2, 1);
  glVertexAttribDivisor(pos3, 1);
  glVertexAttribDivisor(pos4, 1);
}

void SpriteRenderer::cleanup() {
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &sprite_shape_);
}

void SpriteRenderer::rebuildVBO() {
  if (capacity < sprites.capacity()) {
    glDeleteBuffers(1, &vbo);
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * sprites.capacity(),
                 sprites.data(), GL_DYNAMIC_DRAW);
    capacity = sprites.capacity();
    reset_vao();
    return;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sprites.capacity(), sprites.data());
}

void SpriteRenderer::render() {
  glUseProgram(program);
  glBindVertexArray(vao);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, sprites.size());
}
