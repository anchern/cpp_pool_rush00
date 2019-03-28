//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Bullet.hpp"

Bullet::Bullet(char type, t_location const &location, unsigned int damage) :
_type(type), _location(location)
{
	this->_damage = damage;
}

Bullet::Bullet()
{
	_type = '*';
	_location.x = -1;
	_location.y = -1;
	_damage = 1;
	_speed = 2;
}


GameEntity *Bullet::getType()
{
	return ((GameEntity *)this);
}

unsigned int Bullet::get_damage() const
{
	return _damage;
}

const t_location &Bullet::get_location() const
{
	return _location;
}

void Bullet::set_location(const t_location &_location)
{
	Bullet::_location = _location;
}
