cmake_minimum_required(VERSION 3.5)

project(score-calculator)

find_package(GTest REQUIRED)

set(SCORE_CALCULATOR_SOURCES
  src/fu_han.cpp
  src/hand.cpp
  src/meld.cpp
  src/parser.cpp
  src/winning_hand.cpp
  src/yaku.cpp)

set(SCORE_CALCULATOR_HEADERS
  src/config.hpp
  src/core.hpp
  src/fu_han.hpp
  src/hand.hpp
  src/meld.hpp
  src/parser.hpp
  src/result.hpp
  src/score.cpp
  src/score.hpp
  src/tile.hpp
  src/types.hpp
  src/winning_hand.hpp
  src/yaku.hpp)

add_library(score_calculator
  ${SCORE_CALCULATOR_SOURCES}
  ${SCORE_CALCULATOR_HEADERS})
target_compile_features(score_calculator PUBLIC cxx_std_23)
target_compile_options(score_calculator PUBLIC
  $<$<CONFIG:DEBUG>:-O0 -Wall -Wextra -g>
  $<$<CONFIG:Release>:-O3 -Wall -Wextra>)

set_target_properties(score_calculator PROPERTIES PUBLIC_HEADER "${SCORE_CALCULATOR_HEADERS}")

install(TARGETS score_calculator
  EXPORT ScoreCalculator
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/score_calculator)
install(EXPORT ScoreCalculator
  FILE ScoreCalculatorConfig.cmake
  DESTINATION share/cmake)

enable_testing()

add_executable(score_calculator_test
  tests/fu_han_test.cpp
  tests/parser_test.cpp
  tests/score_test.cpp
  tests/winning_hand_test.cpp)
target_include_directories(score_calculator_test PRIVATE src)
target_link_libraries(score_calculator_test PRIVATE
  score_calculator
  GTest::GTest
  GTest::Main)

include(GoogleTest)
gtest_discover_tests(score_calculator_test)
