//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "GameEntity.hpp"

void GameEntity::move(int degrees)
{
	this->_location.x += (int)std::round(std::cos(degrees)) * _speed;
	this->_location.y += (int)std::round(std::sin(degrees)) * _speed;
}

int GameEntity::get_speed() const
{
	return _speed;
}

void GameEntity::set_speed(int _speed)
{
	GameEntity::_speed = _speed;
}
