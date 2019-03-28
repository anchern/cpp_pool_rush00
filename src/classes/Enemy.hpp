//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#ifndef RUSH00_ENEMY_HPP
#define RUSH00_ENEMY_HPP

#include "includes.h"
#include "Weapon.hpp"
#include "Character.hpp"

class Enemy : public Character
{
public:
	virtual  void setWeapon(Weapon weapon) = 0;
protected:
	t_location	location;
	unsigned	_hp;
	unsigned	_maxHp;
};


#endif //RUSH00_ENEMY_HPP
