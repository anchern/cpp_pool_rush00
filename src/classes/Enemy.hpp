#ifndef RUSH00_ENEMY_HPP
#define RUSH00_ENEMY_HPP

#include "../../includes/includes.h"
#include "Weapon.hpp"
#include "Character.hpp"

class Enemy : public Character
{
public:
	virtual  void setWeapon(const Weapon &weapon) = 0;
	virtual ~Enemy() = default;
protected:
	t_location	location = {-1, -1};
	unsigned	_hp = 0;
	unsigned	_maxHp = 1;
};


#endif //RUSH00_ENEMY_HPP
