#include "bettergl/MathTypes.hpp"
#include <AtlasLoader.hpp>
#include <cjson/cJSON.h>
#include <iostream>

Atlas &Atlas::load(const char *atlas_data, int width__, int height__) {
  cJSON *json = cJSON_Parse(atlas_data);
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      cJSON_Delete(json);
      throw std::string("cJSON: Error before: ") + (const char *)error_ptr +
          "\n";
    } else {
      cJSON_Delete(json);
      throw "texture atlas: no data from json";
    }
  }

  if (!cJSON_IsArray(json)) {
    cJSON_Delete(json);
    throw "texture atlas: given json is not a array";
  }

  int length = cJSON_GetArraySize(json);
  for (int i = 0; i < length; i++) {
    cJSON *obj = cJSON_GetArrayItem(json, i);

    if (!cJSON_IsObject(obj)) {
      cJSON_Delete(json);
      throw "texture atlas: array element is not an object";
    }

    cJSON *name_ = cJSON_GetObjectItem(obj, "name");
    cJSON *x_ = cJSON_GetObjectItem(obj, "x");
    cJSON *y_ = cJSON_GetObjectItem(obj, "y");
    cJSON *width_ = cJSON_GetObjectItem(obj, "width");
    cJSON *height_ = cJSON_GetObjectItem(obj, "height");

    if (name_ == nullptr || x_ == nullptr || y_ == nullptr ||
        width_ == nullptr || height_ == nullptr) {
      cJSON_Delete(json);
      throw "texture atlas: array element is missing a field";
    }

    if (!cJSON_IsString(name_) || !cJSON_IsNumber(x_) || !cJSON_IsNumber(y_) ||
        !cJSON_IsNumber(width_) || !cJSON_IsNumber(height_)) {
      cJSON_Delete(json);
      throw "texture atlas: array element field has wrong type";
    }

    std::string name = name_->valuestring;
    float x = x_->valuedouble / (float)width__;
    float y1 = 1.0 - (y_->valuedouble / (float)height__);
    float x1 = x + (width_->valuedouble / (float)width__);
    float y = y1 - (height_->valuedouble / (float)height__);
    bgl::vec4 tmp{x, y, x1, y1};
    data.insert_or_assign(name, tmp);
  }

  cJSON_Delete(json);
  return *this;
}
