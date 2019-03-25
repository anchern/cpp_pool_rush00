//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Bullet.hpp"

Bullet::Bullet(unsigned int damage, char type)
{
	_damage = damage;
	_type = type;
}


GameEntity* Bullet::getType()
{
	return (this);
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
