#include <bettergl/Debugging.hpp>
#include <bettergl/GLTypes.hpp>
#include <bettergl/MathTypes.hpp>
#include <bettergl/Program.hpp>
#include <GLFW/glfw3.h>

#include "fragment.glsl.hpp"
#include "vertex.glsl.hpp"

typedef struct Vertex {
  bgl::vec2 pos;
  bgl::vec3 col;
} Vertex;

static const Vertex vertices[3] = {{{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
                                   {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
                                   {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL(); // only then we can load
  glfwSwapInterval(1);
  bgl::setUpDebugger();

  // GLint numExtensions;
  // glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
  // std::cout << "- Extensions" << std::endl;
  // for (GLint i = 0; i < numExtensions; i++) {
  //   std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
  // }

  bgl::beginDebugGroup(1, "setting up vbo");
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  bgl::endDebugGroup();

  bgl::beginDebugGroup(1, "gex");
  bgl::Program program =
      bgl::createProgram("main program", vertex.getRes().c_str(),
                         fragment.getRes().c_str())
          .unwrapExit();
  bgl::endDebugGroup();

  const GLint mvp_location = glGetUniformLocation(program, "MVP");
  const GLint vpos_location = glGetAttribLocation(program, "vPos");
  const GLint vcol_location = glGetAttribLocation(program, "vCol");

  bgl::beginDebugGroup(1, "setting up vao");

  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  bgl::labelObject(GL_VERTEX_ARRAY, vertex_array, "vertex array");
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, col));
  bgl::endDebugGroup();

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    bgl::beginDebugGroup(1, "rendering triangle");
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    bgl::endDebugGroup();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
