cmake_minimum_required (VERSION 2.8)
project (cmosocket)

set (lib_SRC
  src/lib/cmo_vector.c
  src/lib/cmosocket.c
)

add_library (cmosocket ${lib_SRC})
include_directories ("${PROJECT_SOURCE_DIR}/include")

set_target_properties (cmosocket
  PROPERTIES COMPILE_FLAGS "-ansi -pedantic -Wall -Werror"
)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Debug")
  set_target_properties (cmosocket
    PROPERTIES COMPILE_FLAGS "-ansi -pedantic -Wall -Werror -g -ggdb"
  )
endif()

enable_testing()
add_subdirectory(test)
