#include "Player.hpp"

Player::Player(const std::string &name) : _name(name)
{
	_location.x = WIDTH / 2;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER_1 + 1);
	_maxHp = 3;
	_hp = _maxHp;
	_degrees = 90;
	this->_damage = 0;
}

Player::Player()
{
	_location.x = WIDTH / 2 - WIDTH_PLAYER_1 / 2;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER_1 + 1);
	_maxHp = 3;
	_hp = _maxHp;
	_degrees = 90;
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

unsigned int Player::get_hp() const
{
	return _hp;
}

unsigned int Player::get_maxHp() const
{
	return _maxHp;
}

t_location Player::getLocation()
{
	return _location;
}
