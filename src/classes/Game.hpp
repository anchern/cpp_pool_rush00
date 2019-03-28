//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#ifndef RUSH00_GAME_HPP
#define RUSH00_GAME_HPP


#include <ctime>
#include "Player.hpp"
#include "GameEntity.hpp"
#include "StandartUnit.hpp"
#include "includes.h"

#define NUMBEROFPLAYERS 2
#define STANDART_UNITS_NUMBER 50


class Game
{
public:
	static Game &instance();

	char &getField(int i, int j);
	GameEntity *getGameEntitys(int i, int j) const;
	Player &getPlayers(int i);
	const StandartUnit *getStandartUnits() const;
	t_bullet *getBullets() const;

private:
	Game() = default;
	Game(Game const &);
	Game &operator=(Game const &);


	time_t time = 0;
	unsigned score = 0;


	Player players[NUMBEROFPLAYERS];
	StandartUnit StandartUnits[STANDART_UNITS_NUMBER];
	GameEntity *gameEntitys[HEIGHT][WIDTH];
	t_bullet *bullets;

	char field[HEIGHT][WIDTH];
};


#endif //RUSH00_GAME_HPP
