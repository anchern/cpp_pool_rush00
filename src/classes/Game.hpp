//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#ifndef RUSH00_GAME_HPP
#define RUSH00_GAME_HPP


#include <ctime>
#include "Player.hpp"
#include "GameEntity.hpp"
#include "StandardUnit.hpp"
#include "../../includes/includes.h"



#define NUMBEROFPLAYERS 2
#define STANDART_UNITS_NUMBER 50

static std::ofstream file;

class Game
{
public:
	static Game &instance();
	void setBullets(t_bullet *bullets);
	char &getField(int i, int j);
	GameEntity *getGameEntitys(int i, int j) const;
	void setGameEntitys(int i, int j, GameEntity *gameEntity);
	void setFieldElem(int i, int j, char c);
	Player *getPlayers();
	StandardUnit *getStandartUnits();
	t_bullet *getBullets() const;
	void	clsField();
	void	clsGameEntities();
	void	printField();
	char	*getOneLineField();



private:
	Game();
	Game(Game const &);
	Game &operator=(Game const &);


	time_t time = 0;
	unsigned score = 0;

public:
	void setScore(unsigned int score);

private:
	Player players[NUMBEROFPLAYERS];
	StandardUnit StandartUnits[STANDART_UNITS_NUMBER];
	GameEntity *gameEntities[HEIGHT][WIDTH];
	t_bullet *bullets;
public:
	unsigned int getScore() const;

private:

	char field[HEIGHT][WIDTH + 1];
};


#endif //RUSH00_GAME_HPP
