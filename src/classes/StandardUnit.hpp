//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#ifndef RUSH00_STANDARTUNIT_HPP
#define RUSH00_STANDARTUNIT_HPP

#include "Enemy.hpp"
#define HEGHT_STANDARD_UNIT 3
#define WIDTH_STANDARD_UNIT 6


class StandardUnit : public Enemy
{
public:
	explicit StandardUnit(t_location location);
	StandardUnit();

	void		setLocation(t_location const &location);
	void		setWeapon(const Weapon &weapon);
	GameEntity	*getType();

	t_bullet	*shot(t_bullet *bullets_list);
	void		death();

	void takeDamage(Bullet &bullet);
	void	move(int degrees);

private:
	Weapon _weapon;
public:
	char avatar[HEGHT_STANDARD_UNIT][WIDTH_STANDARD_UNIT] = {" .-. ",
															 "(@ @)",
															 " \\-/ "};

};


#endif //RUSH00_STANDARTUNIT_HPP
