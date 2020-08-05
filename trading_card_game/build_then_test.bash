#!/bin/bash

cmake -H. -Bbuild
cmake --build build/ -- -j $(nproc)
./build/bin/trading_card_tests