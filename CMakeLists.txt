cmake_minimum_required(VERSION 3.23)
project(SpaceGamingZombies LANGUAGES CXX)
include(deps/ext.cmake)

betterGL_bytepack(vertex src/shaders/vertex.glsl vertex.glsl r)
betterGL_bytepack(fragment src/shaders/fragment.glsl fragment.glsl)

add_executable(main src/main.cpp)
target_link_libraries(main glfw betterGL vertex fragment)
