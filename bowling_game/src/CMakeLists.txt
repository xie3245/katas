# Generic test that uses conan libs
add_library(bowling_game_lib STATIC "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp")
target_link_libraries(
  bowling_game_lib
  PUBLIC project_options
          project_warnings
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)

add_library(Game::Bowling ALIAS bowling_game_lib)
target_include_directories(bowling_game_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(bowling_game "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(
  bowling_game
  PRIVATE Game::Bowling)
