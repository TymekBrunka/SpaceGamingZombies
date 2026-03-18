#pragma once
#include "bettergl/MathTypes.hpp"
#include <string>
#include <unordered_map>

struct Atlas {
public:
  std::unordered_map<std::string, bgl::vec4> data;
};
