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
        src/classes/Game.hpp src/classes/StandardUnit.cpp
        src/classes/StandardUnit.hpp src/CreateNewBullet.cpp
        src/DeleteBullets.cpp src/main.cpp src/CreateGame.cpp
        src/SetEntityOnField.cpp src/StandardUnitGeneration.cpp
        src/moveGameEntities.cpp src/checkCollision.cpp
        src/deleteDeathEntities.cpp src/menu.cpp src/print_game_over.cpp src/classes/ClientServer.cpp src/classes/ClientServer.hpp src/playersActions.cpp src/soloServerClientModes.cpp src/score.cpp src/BackgroundActions.cpp)

target_link_libraries(rush00 -lncurses)
