cmake_minimum_required(VERSION 3.23)
project(SpaceGamingZombies LANGUAGES CXX)
include(deps/ext.cmake)

betterGL_bytepack(vertex src/shaders/vertex.glsl vertex.glsl r)
betterGL_bytepack(fragment src/shaders/fragment.glsl fragment.glsl)

add_library(app SHARED src/App.cpp)
target_include_directories(app PRIVATE src)
target_link_libraries(app PUBLIC
  glfw
  $<$<CONFIG:DEBUG>:betterGL_dynamic>
  $<$<CONFIG:RELEASE>:betterGL_static>

  vertex
  fragment
)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)
target_link_libraries(
  main
  app
)
# add_dependencies(main betterGL_dynamic_dependant)

bettergl_cpdlls(main)
