//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "GameEntity.hpp"

void GameEntity::move(int degrees)
{
	this->_location.x -= (int)std::round(std::cos(degrees * M_PI / 180 )) *
			_speed;
	this->_location.y -= (int)std::round(std::sin(degrees * M_PI / 180)) *
			_speed;
}

int GameEntity::get_speed() const
{
	return _speed;
}

void GameEntity::set_speed(int _speed)
{
	GameEntity::_speed = _speed;
}

const t_location &GameEntity::get_location() const
{
	return _location;
}

int GameEntity::get_degrees() const
{
	return _degrees;
}

unsigned int GameEntity::get_damage() const
{
	return _damage;
}

void GameEntity::set_degrees(int _degrees)
{
	GameEntity::_degrees = _degrees;
}
