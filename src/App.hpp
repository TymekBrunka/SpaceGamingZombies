#pragma once
#include "SpriteRenderer.hpp"
#include <array>
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <mutex>

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

public:
  App() = default;
  void init(const char* title);
  void cleanup();

  std::mutex inputMutex;
  std::array<int16_t, 2> input;

  std::mutex renderMutex;
  SpriteRenderer mainRenderer;

  void resize(int width, int height);
};
