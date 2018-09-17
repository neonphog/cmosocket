cmake_minimum_required (VERSION 2.8)
project (cmosocket_tests)

add_subdirectory (Criterion)
include_directories (Criterion/include)
include_directories (../src)

set (TESTS
  vector.c
)

foreach (testfile ${TESTS})
  add_executable (${testfile}.bin ${testfile})
  target_link_libraries(${testfile}.bin criterion)
  target_link_libraries(${testfile}.bin cmosocket)
  add_test (${testfile} ${testfile}.bin)
endforeach()
