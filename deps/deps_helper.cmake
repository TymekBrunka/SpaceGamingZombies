if (NOT DEFINED CMAKE_PREFIX_PATH)
  set(CACHE{CMAKE_PREFIX_PATH} TYPE INTERNAL HELP "" FORCE VALUE "")
endif()

if (NOT DEFINED CM_THIRDPARTY)
  set(CACHE{CM_THIRDPARTY} TYPE INTERNAL HELP "" FORCE VALUE $ENV{CM_THIRDPARTY})
endif()

set(CACHE{CM_DOWNLOAD_DIR} TYPE INTERNAL HELP "" FORCE VALUE ${CMAKE_BINARY_DIR}/cmdeps)
make_directory(${CMAKE_BINARY_DIR}/cmdeps/)
set(CACHE{CM_INSTALL_DIR} TYPE INTERNAL HELP "" FORCE VALUE ${CMAKE_BINARY_DIR}/installed)
make_directory(${CMAKE_BINARY_DIR}/installed/)

if (NOT CM_THIRDPARTY EQUAL UNDEFINED)
  message("Global installs enabled")
  set(dir ${CM_THIRDPARTY}/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM_NAME})

  if (NOT EXISTS ${dir}/cmdeps/)
    make_directory(${dir}/cmdeps)
  endif()
  if (NOT EXISTS ${dir}/installed/)
    make_directory(${dir}/installed)
  endif()

  set(CACHE{CM_DOWNLOAD_DIR} TYPE INTERNAL HELP "" FORCE VALUE ${dir}/cmdeps)
  set(CACHE{CM_INSTALL_DIR} TYPE INTERNAL HELP "" FORCE VALUE ${dir}/installed)

  set(cmak_pref_paf ${CMAKE_PREFIX_PATH})
  list(APPEND cmak_pref_paf ${CM_INSTALL_DIR}/lib/cmake/)
  set(CACHE{CMAKE_PREFIX_PATH} TYPE INTERNAL HELP "" FORCE VALUE ${cmak_pref_paf})
  message("cmak pref paf: " ${CMAKE_PREFIX_PATH})
endif()
message(">>> Dependency download dir: ${CM_DOWNLOAD_DIR}")
message(">>> Dependency install dir: ${CM_INSTALL_DIR}")

include(ExternalProject)

macro (install)
endmacro ()

# macro (find_package)
# endmacro ()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  message("Ccache enabled")
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM} base_dir=${PROJECT_SOURCE_DIR} hash_dir=false)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM} base_dir=${PROJECT_SOURCE_DIR} hash_dir=false)
endif()
