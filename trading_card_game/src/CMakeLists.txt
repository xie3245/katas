# Generic test that uses conan libs
set(PROJECT_LIB_NAME ${PROJECT_NAME}_lib)
set(PROJECT_LIB_ALIAS ${PROJECT_NAME}_tests)

add_library(${PROJECT_LIB_NAME} STATIC "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp")
target_link_libraries(
  ${PROJECT_LIB_NAME}
  PUBLIC project_options
          project_warnings
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)

add_library(Game::TradingCard ALIAS ${PROJECT_LIB_NAME})
target_include_directories(${PROJECT_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE Game::TradingCard)
