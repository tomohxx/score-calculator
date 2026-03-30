cmake_minimum_required(VERSION 3.12)

project(score-calculator LANGUAGES CXX)

include(GNUInstallDirs)

find_package(GTest QUIET)

add_library(score_calculator
  src/fu_han.cpp
  src/hand.cpp
  src/meld.cpp
  src/parser.cpp
  src/score.cpp
  src/tile.cpp
  src/winning_hand.cpp
  src/yaku.cpp)
target_compile_features(score_calculator PUBLIC cxx_std_23)
target_compile_options(score_calculator PUBLIC
  $<$<CONFIG:Debug>:-O0 -Wall -Wextra -g>
  $<$<CONFIG:Release>:-O3 -Wall -Wextra>)
target_include_directories(score_calculator PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS score_calculator
  EXPORT ScoreCalculator
  LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/mahjong DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ScoreCalculator
  FILE ScoreCalculatorConfig.cmake
  NAMESPACE ScoreCalculator::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mahjong)

if(GTest_FOUND)
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
  target_compile_options(score_calculator_test PRIVATE -Wno-missing-field-initializers)

  include(GoogleTest)
  gtest_discover_tests(score_calculator_test)
else()
  message(STATUS "GTest not found; tests are disabled")
endif()
