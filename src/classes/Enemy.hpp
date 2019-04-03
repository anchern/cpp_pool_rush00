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
};


#endif //RUSH00_ENEMY_HPP
