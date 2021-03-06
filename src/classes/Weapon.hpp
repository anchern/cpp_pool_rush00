#ifndef RUSH00_WEAPON_HPP
#define RUSH00_WEAPON_HPP

#include "Bullet.hpp"
#include "../../includes/includes.h"


class Weapon
{
public:
	explicit Weapon(t_location const &location, char avatar = 'A');
	Weapon();

	const t_location &get_location() const;

	t_bullet *shot(t_bullet *bullets_list, int degrees);
	void set_bullet(const Bullet &_bullet);

	void set_location(t_location location);

	const Bullet &get_bullet() const;

private:
	t_location	_location;
	char 		_avatar;
	unsigned	_level = 1;
	Bullet		_bullet;
};


#endif //RUSH00_WEAPON_HPP
