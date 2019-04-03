//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_INCLUDES_H
#define C_POOL_INCLUDES_H

#define HEIGHT	50
#define WIDTH	50

#include <iostream>
#include <cmath>


class Bullet;
class Game;
class StandardUnit;
class GameEntity;

typedef struct	s_location
{
	int x;
	int y;
}				t_location;

typedef struct	s_bullet
{
	Bullet *bullet;
	struct s_bullet *next;
}				t_bullet;

t_bullet	*push_bullet_front(t_bullet *bullet, Bullet *bullet1);
Bullet *default_bullet_elem(t_location const &location);
void	initGame(Game &game, const std::string &player_name_1);
void	setEntitiesOnField(Game &game);
void	setEntitiesOnPrintField(Game &game);
void	standardUnitGeneration(Game &game);
void 	movePlayer(Game &game);
void	moveBullets(Game &game);
void	moveStantardUnits(Game &game);
void	checkCollision(GameEntity *GE1, GameEntity *GE2, Game &game);
void	delete_bullet(t_bullet *bullet, Bullet *bullet1);


#endif //C_POOL_INCLUDES_H
