//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_INCLUDES_H
#define C_POOL_INCLUDES_H

#define HEIGHT	800
#define WIDTH	400

#include <iostream>
#include <cmath>


class Bullet;
class Game;

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

void	push_bullet_front(t_bullet *bullet, Bullet *bullet1);
Bullet *default_bullet_elem(t_location const &location);
void	initGame(Game &game, const std::string &player_name_1);

#endif //C_POOL_INCLUDES_H
