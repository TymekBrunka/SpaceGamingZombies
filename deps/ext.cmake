include(deps/deps_helper.cmake)
include(deps/CPM.cmake)

message("-- bettergl")
CPMAddPackage(
  NAME bettergl
  VERSION 0.0.6
  GITHUB_REPOSITORY TymekBrunka/bettyergl
  GIT_TAG main
  OPTIONS
    "BETTERGL_BUILD_TEST_EXAMPLE OFF"
)

message("-- glfw 3.4")
find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
  ExternalProject_Add(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
    CMAKE_ARGS
      "--install-prefix=${CM_INSTALL_DIR}"
      "-DGLFW_BUILD_EXAMPLES=OFF"
      "-DGLFW_BUILD_TESTS=OFF"
      "-DGLFW_BUILD_DOCS=OFF"
    CONFIGURE_HANDLED_BY_BUILD ON
    PREFIX ${CM_DOWNLOAD_DIR}
    INSTALL_DIR "${CM_INSTALL_DIR}"
  )
endif()

message("-- cJSON 1.7.19")
find_package(cJSON 1.7.19 QUIET)
if (NOT cJSON_FOUND)
  ExternalProject_Add(
    cJSON
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON
    GIT_TAG v1.7.19
    GIT_SHALLOW TRUE
    CMAKE_ARGS
      "--install-prefix=${CM_INSTALL_DIR}"
      "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
    CONFIGURE_HANDLED_BY_BUILD ON
    PREFIX ${CM_DOWNLOAD_DIR}
    INSTALL_DIR "${CM_INSTALL_DIR}"
  )
endif()

# message("-- nlohmann_json 3.12")
# find_package(nlohmann_json 3.12 QUIET)
# if (NOT nlohmann_json_FOUND)
#   ExternalProject_Add(
#     nlohmann_json
#     GIT_REPOSITORY https://github.com/nlohmann/json
#     GIT_TAG v3.12.0
#     GIT_SHALLOW TRUE
#     CMAKE_ARGS
#       "--install-prefix=${CM_INSTALL_DIR}"
#       "-DJSON_BuildTests_INIT=OFF"
#     CONFIGURE_HANDLED_BY_BUILD ON
#     PREFIX ${CM_DOWNLOAD_DIR}
#     INSTALL_DIR "${CM_INSTALL_DIR}"
#   )
# endif()

message("-- glm 1.0.3")
CPMAddPackage(
  NAME glm
  VERSION 1.0.3
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 1.0.3
  OPTIONS
    "GLM_ENABLE_CXX_20 ON"
)
