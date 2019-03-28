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



void Weapon::shot(t_bullet *bullets_list, int degrees)
{

	push_bullet_front(bullets_list, new Bullet(_bullet));
	bullets_list->bullet->set_location(this->_location);
	bullets_list->bullet->move(degrees);
}

const t_location &Weapon::get_location() const
{
	return _location;
}

void Weapon::set_bullet(const Bullet &_bullet)
{
	Weapon::_bullet = _bullet;
}
