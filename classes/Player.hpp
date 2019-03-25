//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_PLAYER_HPP
#define C_POOL_PLAYER_HPP

#include "../includes/includes.h"
#include "Character.hpp"
#include <string>

#define WIDTH_PLAYER 4
#define HEIGHT_PLAYER 7

class Player : public Character
{
public:
	explicit Player(const std::string &name);

	void setWeapon(Weapon weapon);

	void takeDamage(Bullet bullet);
	void death();
	void shot();


private:
	std::string	_name;
	Weapon		_weapon[3];
	unsigned	_hp;
	unsigned	_maxHp;
	char		_avatar[4][8] =  {"   ^   ",
								  "  ( )  ",
								  " /| |\\ ",
								  "/_|||_\\"};

	t_location	_location;
};

#endif //C_POOL_PLAYER_HPP







