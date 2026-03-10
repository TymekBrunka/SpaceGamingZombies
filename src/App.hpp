#pragma once
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <GLFW/glfw3.h>

class App {
  GLFWwindow *window;
  bgl::Program program;
  bgl::VAO vao;

  void create_window(const char* title);
  void set_up();
  void render_loop();
  void cleanup();
public:
  App();
  App(const char* title);
};
