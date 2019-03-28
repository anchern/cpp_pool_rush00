#include <utility>

//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Player.hpp"

Player::Player(const std::string &name) : _name(name)
{
	_location.x = WIDTH / 2;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER + 1);
	_maxHp = 3;
	_hp = _maxHp;
	this->_damage = 0;
}

void Player::takeDamage(Bullet bullet)
{
	if (bullet.get_damage() > _hp)
		_hp = 0;
	_hp -= bullet.get_damage();
}

void Player::death()
{

}

void Player::shot()
{
	int i;

	i = 0;
	while (i < 3 && _weapon[i].get_location().x != -1)
	{
		_weapon[i].shot();
		i++;
	}
}


void Player::setWeapon(Weapon weapon, int i)
{
	_weapon[i] = std::move(weapon);
}

GameEntity* Player::getType()
{
	return ((GameEntity*)this);
}