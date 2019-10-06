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



#define STANDART_UNITS_NUMBER 50
#define MAX_PLAYERS 2

extern int numberOfPlayers;


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
    void setScore(unsigned int score);
    unsigned int getScore() const;



private:
	Game();
	Game(Game const &);
	Game &operator=(Game const &);


	time_t time = 0;
	unsigned score = 0;
	Player players[MAX_PLAYERS];
	StandardUnit StandartUnits[STANDART_UNITS_NUMBER];
	GameEntity *gameEntities[HEIGHT][WIDTH];
	t_bullet *bullets;
	char field[HEIGHT][WIDTH + 1];


};


#endif //RUSH00_GAME_HPP
