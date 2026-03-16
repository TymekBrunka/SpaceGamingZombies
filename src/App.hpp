#pragma once
#include "SpriteRenderer.hpp"
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>

class App {
public:
  float aspectRatio;
  bgl::vec2 pixelSize;
  int windowSize[2];

  bgl::Texture2D spritesheet;
private:
  bgl::VAO vao;
  bgl::Program program;
  GLFWwindow *window;

  void create_window(const char *title);
  void set_up();
  void render_loop();

  SpriteRenderer mainRenderer;

public:
  App() = default;
  void init(const char* title);
  void cleanup();

  void resize(int width, int height);
};
