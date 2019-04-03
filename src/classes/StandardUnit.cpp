//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#include "StandardUnit.hpp"

StandardUnit::StandardUnit(t_location location)
{
	this->_damage = 0;
	this->_location = location;
}

StandardUnit::StandardUnit()
{
	this->_damage = 0;
	this->_location.x = -1;
	this->_location.y = -1;
	_maxHp = 1;
	_hp = _maxHp;
	_degrees = 270;
}

void StandardUnit::setWeapon(const Weapon &weapon)
{
	_weapon = weapon;
}

void StandardUnit::setLocation(t_location const &location)
{
	this->_location = location;
}

GameEntity* StandardUnit::getType()
{
	return ((GameEntity *)this);
}

t_bullet *StandardUnit::shot(t_bullet *bullets_list)
{
	bullets_list = _weapon.shot(bullets_list, this->_degrees);
	return (bullets_list);
}

void StandardUnit::death()
{
	this->_location.x = -1;
	this->_location.y = -1;
}

void StandardUnit::takeDamage(Bullet &bullet)
{
	if (bullet.get_damage() > _hp)
		_hp = 0;
	_hp -= bullet.get_damage();
}

