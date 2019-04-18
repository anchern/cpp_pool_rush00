#include "Player.hpp"
#include "ncurses.h"
#include "unistd.h"

Player::Player(const std::string &name) : _name(name)
{
	_location.x = WIDTH / 2;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER_1 + 1);
	_maxHp = 3;
	_hp = _maxHp;
	_degrees = 90;
	this->_damage = -1;
}

Player::Player()
{
	_location.x = 0;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER_1 + 1);
	_maxHp = 5;
	_hp = _maxHp;
	_degrees = 90;
	_speed = 1;
	this->_damage = -1;
}

void Player::takeDamage(Bullet &bullet)
{
	if (bullet.get_damage() >= _hp)
		_hp = 0;
	else
		_hp -= bullet.get_damage();
}









void Player::death()
{
	this->_hp = 0;
}

t_bullet *Player::shot(t_bullet *bullets_list)
{
	int i;

	i = 0;
	while (i < 3 && _weapon[i].get_location().x != -1)
	{
		bullets_list = _weapon[i].shot(bullets_list, this->_degrees);
		i++;
	}
	return (bullets_list);
}


void Player::setWeapon(Weapon weapon, int i)
{
	_weapon[i] = std::move(weapon);
}

GameEntity* Player::getType()
{
	return ((GameEntity*)this);
}

void Player::setName(const std::string &_name)
{
	this->_name = _name;
}

const std::string &Player::get_name() const
{
	return _name;
}

const Weapon *Player::get_weapon() const
{
	return _weapon;
}

t_location Player::getLocation()
{
	return _location;
}

void Player::move(int degrees)
{
	t_location tmp_loc;

	this->_location.x -= (int)std::round(std::cos(degrees * M_PI / 180 ));
	this->_location.y -= (int)std::round(std::sin(degrees * M_PI / 180));
	if (_location.x  + WIDTH_PLAYER_1 - 1 > WIDTH || _location.x < 0 || _location
	.y + HEIGHT_PLAYER_1 > HEIGHT ||
		_location.y < 0)
	{
		this->_location.x += (int)std::round(std::cos(degrees * M_PI / 180));
		this->_location.y += (int)std::round(std::sin(degrees * M_PI / 180));
	}
	tmp_loc = _location;
	tmp_loc.x = _location.x + ((WIDTH_PLAYER_1 - 1) / 2);
	_weapon[0].set_location(tmp_loc);
}

void Player::set_avatar(std::string *avatar)
{
	for (int i = 0; i < HEIGHT_PLAYER_1; i++)
		strncpy(_avatar[i], avatar[i].c_str(), WIDTH_PLAYER_1 - 1);
}
