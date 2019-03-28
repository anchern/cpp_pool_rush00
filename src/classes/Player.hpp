//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_PLAYER_HPP
#define C_POOL_PLAYER_HPP

//#include "includes.h"
#include "Character.hpp"
#include "Weapon.hpp"
#include <string>


#define WIDTH_PLAYER 10
#define HEIGHT_PLAYER 10

class Player : public Character
{
public:
	explicit Player(const std::string &name);
	Player();

	void setWeapon(Weapon weapon, int i);

	void setName(const std::string &_name);

	void takeDamage(Bullet bullet);
	void death();
	void shot(t_bullet *bullets_list);

	GameEntity *getType();

	const std::string &get_name() const;

private:
	std::string	_name;
	Weapon		_weapon[3];
	unsigned	_hp;
	unsigned	_maxHp;
public:
	char		_avatar[HEIGHT_PLAYER][WIDTH_PLAYER] =  {	"   ^   ",
												 			"  (4)  ",
												 			" /|2|\\ ",
												 			"/_|||_\\"};
};

#endif //C_POOL_PLAYER_HPP







