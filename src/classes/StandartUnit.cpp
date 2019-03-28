//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#include "StandartUnit.hpp"

StandartUnit::StandartUnit(t_location location)
{
	this->_damage = 0;
	this->location = location;
}

StandartUnit::StandartUnit()
{
	this->_damage = 0;
	this->location.x = -1;
	this->location.y = -1;
	_degrees = 270;
}

void StandartUnit::setWeapon(const Weapon &weapon)
{
	_weapon = weapon;
}

void StandartUnit::setLocation(t_location const &location)
{
	this->location = location;
}

GameEntity* StandartUnit::getType()
{
	return ((GameEntity *)this);
}

void StandartUnit::shot(t_bullet *bullets_list)
{
	_weapon.shot(bullets_list);
}

void StandartUnit::death()
{}

