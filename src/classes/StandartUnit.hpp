//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#ifndef RUSH00_STANDARTUNIT_HPP
#define RUSH00_STANDARTUNIT_HPP

#include "Enemy.hpp"


class StandartUnit : public Enemy
{
public:
	explicit StandartUnit(t_location location);
	StandartUnit();

	void		setLocation(t_location const &location);
	void		setWeapon(const Weapon &weapon);
	GameEntity	*getType();

	t_bullet	*shot(t_bullet *bullets_list);
	void		death();
	void		takeDamage(Bullet bullet) {}

private:
	Weapon _weapon;
	char avatar[2][3];

};


#endif //RUSH00_STANDARTUNIT_HPP
