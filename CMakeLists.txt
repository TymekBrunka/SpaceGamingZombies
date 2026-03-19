cmake_minimum_required(VERSION 3.23)
project(SpaceGamingZombies LANGUAGES CXX)
include(deps/ext.cmake)

betterGL_bytepack(vertex assets/shaders/vertex.glsl vertex.glsl)
betterGL_bytepack(fragment assets/shaders/fragment.glsl fragment.glsl)

betterGL_imgpack(SPRITES assets/textures/spritesheet.png sprites.png n 4)
betterGL_bytepack(SPRITES_atlas_json assets/textures/spritesheet.json spritesheet.json)

add_library(app SHARED
  src/App.cpp
  src/SpriteRenderer.cpp
  src/AtlasLoader.cpp
)

target_include_directories(app PRIVATE src)
target_link_libraries(app PUBLIC
  glfw
  glm::glm
  bettergl_stbimage
  cjson
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
