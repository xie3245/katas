#!/bin/bash

cmake -H. -Bbuild
cmake --build build/ -- -j $(nproc)
./build/bin/bowling_game_tests