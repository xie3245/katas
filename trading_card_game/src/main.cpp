#include <spdlog/spdlog.h>
#include <iostream>



int main(int, const char**)
{
  spdlog::info("Hello, {}!", "World");

  fmt::print("Hello, from {}\n", "{fmt}");
}
