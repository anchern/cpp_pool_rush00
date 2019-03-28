//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Weapon.hpp"

Weapon::Weapon(t_location const &location,  char avatar) :
_location(location), _avatar(avatar)
{
}

Weapon::Weapon()
{
	_location.x = -1;
	_location.y = -1;
	_avatar = 'A';
}

void Weapon::shot()
{

}

const t_location &Weapon::get_location() const
{
	return _location;
}
