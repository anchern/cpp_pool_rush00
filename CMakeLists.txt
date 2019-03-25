cmake_minimum_required(VERSION 3.13)
project(rush00)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)
include_directories(includes)

add_executable(rush00
        classes/Bullet.cpp
        classes/Bullet.hpp
        classes/Character.cpp
        classes/Character.hpp
        classes/GameEntity.cpp
        classes/GameEntity.hpp
        classes/Player.cpp
        classes/Player.hpp
        includes/includes.h)
