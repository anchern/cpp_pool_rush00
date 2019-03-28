cmake_minimum_required(VERSION 3.13)
project(rush00)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/classes)
include_directories(includes)

add_executable(rush00
        src/classes/Bullet.cpp
        src/classes/Bullet.hpp
        src/classes/Character.cpp
        src/classes/Character.hpp
        src/classes/GameEntity.cpp
        src/classes/GameEntity.hpp
        src/classes/Player.cpp
        src/classes/Player.hpp
        includes/includes.h src/classes/Weapon.cpp src/classes/Weapon.hpp
        src/classes/Enemy.cpp src/classes/Enemy.hpp src/classes/Game.cpp
        src/classes/Game.hpp src/classes/StandartUnit.cpp
        src/classes/StandartUnit.hpp src/CreateNewBullet.cpp
        src/DeleteBullets.cpp src/main.cpp src/CreateGame.cpp src/SetEntityOnField.cpp)
