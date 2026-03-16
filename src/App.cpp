#include <App.hpp>
#include <GLFW/glfw3.h>
#include <bettergl/Debugging.hpp>
#include <bettergl/Program.hpp>
#include <exception>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stb_image.h>

#include "SpriteRenderer.hpp"

#include "bettergl/GLTypes.hpp"
#include "fragment.glsl.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include "vertex.glsl.hpp"

#include "sprites.png.hpp"

typedef struct Vertex {
  bgl::vec2 pos;
  bgl::vec3 col;
} Vertex;

static bgl::Location aspectRatio_location = 0;
static bgl::Location pixelSize_location = 0;

static const Vertex vertices[3] = {{{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
                                   {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
                                   {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  App *app = reinterpret_cast<App *>(glfwGetWindowUserPointer(window));
  app->resize(width, height);
}

void App::resize(int width, int height) {
  // glfwGetFramebufferSize(window, &width, &height);
  windowSize[0] = width;
  windowSize[1] = height;
  aspectRatio = width / (float)height;
  pixelSize[0] = 1.0f / (float)width;
  pixelSize[1] = 1.0f / (float)height;

  glViewport(0, 0, width, height);
  // glUniform2fv(aspectRatio_location, 1, &aspectRatio);
  glUniform2fv(pixelSize_location, 1, pixelSize);
}

void App::init(const char *title) {
  try {
    create_window(title);
    set_up();
    render_loop();
    cleanup();
  } catch (std::exception &err) {
    std::cout << err.what() << "\n";
  }
}

void App::create_window(const char *title) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

  window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw "Filed to create window";
  }
}

void App::set_up() {
  glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL(); // only then we can load
  glfwSwapInterval(1);
  bgl::setUpDebugger();

  // GLuint vertex_buffer;
  // glGenBuffers(1, &vertex_buffer);
  // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  program = bgl::createProgram("main program", vertex.getRes().c_str(),
                               fragment.getRes().c_str())
                .unwrapExit();

  // aspectRatio_location = glGetUniformLocation(program, "aspectRatio");
  // pixelSize_location = glGetUniformLocation(program, "pixelSize");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  stbi_set_flip_vertically_on_load(true);
  glGenTextures(1, &spritesheet);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, spritesheet);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SPRITES.width, SPRITES.height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, SPRITES.getRes().data);

  mainRenderer.init(program);
  Sprite playerS = {.tex_cords = {0.0, 0.5, 0.25, 1.0},
                    .size = {200, 200}};

  Sprite zombieS = {.tex_cords = {0.0, 0.0, 0.25, 0.5}, .size = {200, 200}};
  mainRenderer.sprites.push_back(playerS);
  mainRenderer.sprites.push_back(zombieS);
  mainRenderer.rebuildVBO();

  // const GLint mvp_location = glGetUniformLocation(program, "MVP");
  // const GLint vpos_location = glGetAttribLocation(program, "vPos");
  //
  // glGenVertexArrays(1, &vao);
  // bgl::labelObject(GL_VERTEX_ARRAY, vao, "vertex array");
  // glBindVertexArray(vao);
  // glEnableVertexAttribArray(vpos_location);
  // glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
  //                       (void *)offsetof(Vertex, pos));
  // glEnableVertexAttribArray(vcol_location);
  // glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
  //                       (void *)offsetof(Vertex, col));
}

void App::render_loop() {
  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    mainRenderer.sprites[1].transforms = glm::rotate(
        glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 0.0f)),
        glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.f, 0.0f, 1.0f));

    mainRenderer.sprites[0].transforms = glm::rotate(
        glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, -50.0f, 0.0f)),
        glm::radians((float)glfwGetTime() * 100.0f), glm::vec3(0.f, 0.0f, -1.0f));

    mainRenderer.rebuildVBO();
    mainRenderer.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void App::cleanup() {
  mainRenderer.cleanup();
  SPRITES.delRes();
  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
