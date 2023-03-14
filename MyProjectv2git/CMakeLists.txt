cmake_minimum_required(VERSION 3.24)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyProject main.cpp Users.cpp Users.h Symbol.cpp Symbol.h Game.cpp Game.h Leaderboard.cpp Leaderboard.h League.cpp League.h TestMode.cpp TestMode.h)
