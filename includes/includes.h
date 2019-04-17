//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_INCLUDES_H
#define C_POOL_INCLUDES_H

#define HEIGHT	60
#define WIDTH	120

#include <cmath>
#include <iostream>
#include "ncurses.h"
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <chrono>

#include <cstdio>
#include <cstdlib>
#include <fstream>

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
void		initSingleGame(Game &game, const std::string &player_name_1);
void		initMultiGame(Game &game, const std::string &player_name_1, const std::string &player_name_2);
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
int 		menu(std::string *menu_items, int size);
int 		client_pause_menu(std::string *menu_items, int size,
								int &client_getch_ref, int socket);



void print_bull_coords(t_bullet *bullets);

#endif //C_POOL_INCLUDES_H
