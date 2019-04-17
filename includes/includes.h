//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_INCLUDES_H
#define C_POOL_INCLUDES_H

#define HEIGHT	60
#define WIDTH	120

#include <iostream>
#include <cmath>
#include <thread>

#define MENU_ITEM 3
#define PAUSE_ITEM 2
#define MULTIPLAYERMENU_ITEM 2
#define NUMBEROFPLAYERS 1
#define STANDART_UNITS_NUMBER 50

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
Bullet		*default_bullet_elem(t_location const &location);
void		initGame(Game &game, const std::string &player_name_1);
void		setEntitiesOnField(Game &game);
void		setEntitiesOnPrintField(Game &game);
void		standardUnitGeneration(Game &game);
void 		movePlayer(Game &game);
void		moveBullets(Game &game);
void		moveStantardUnits(Game &game);
void		checkCollision(GameEntity *GE1, GameEntity *GE2, Game &game);
t_bullet	*delete_bullet(t_bullet *bullet, Bullet *bullet1);
void		setPlayersOnField(Game &game);
void		setStandardUnitsOnField(Game &game);
void		setBulletsOnField(Game &game);
void		standardUnitActions(int j, Game &game);
void		delete_and_move_death_bullets(Game &game);
void		score_calc(Game &game);
void		printField(Game &game, time_t sTime);

int			menu(std::string *menu_items, int size);
void		player1Action(int &getch_ref, Game &game, std::thread &thr1, bool &mut_flag);


void print_bull_coords(t_bullet *bullets);

#endif //C_POOL_INCLUDES_H
