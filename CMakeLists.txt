cmake_minimum_required (VERSION 2.6)
project (cmosocket)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Debug")
endif()

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall -Werror")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -ggdb")

add_library (cmosocket src/lib/cmosocket.c)
include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable (cmosocket_test src/test/test.c)
target_link_libraries (cmosocket_test cmosocket)
