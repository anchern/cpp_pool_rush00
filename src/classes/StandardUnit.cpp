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
	this->_damage = -1;
	this->_location.x = -1;
	this->_location.y = -1;
	_maxHp = 1;
	_hp = _maxHp;
	_degrees = 270;
	_speed = 1;
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
	if (this->_hp != 0)
		this->_hp = 0;
	this->_location.x = -1;
	this->_location.y = -1;
}

void StandardUnit::takeDamage(Bullet &bullet)
{
	if (bullet.get_damage() >= _hp)
		_hp = 0;
	else
		_hp -= bullet.get_damage();
}

void StandardUnit::move(int degrees)
{
	t_location tmp_loc;

	this->_location.x -= (int)std::round(std::cos(degrees * M_PI / 180 ));
	this->_location.y -= (int)std::round(std::sin(degrees * M_PI / 180));
	if (_location.x  + WIDTH_STANDARD_UNIT >= WIDTH || _location.x < 0 || _location
																			.y + HEGHT_STANDARD_UNIT >= HEIGHT ||
		_location.y < 0)
		this->death();
	tmp_loc = _location;
	tmp_loc.x = _location.x + ((WIDTH_STANDARD_UNIT - 1) / 2);
	_weapon.set_location(tmp_loc);
}

