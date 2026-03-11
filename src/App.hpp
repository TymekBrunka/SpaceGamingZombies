#pragma once
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>

class App {
public:
  float aspectRatio;
  bgl::vec2 pixelSize;
  int windowSize[2];

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

  void resize(int width, int height);
};
