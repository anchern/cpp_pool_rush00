//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Player.hpp"

Player::Player(const std::string &name) : _name(name)
{
	_location.x = WIDTH / 2;
	_location.y = HEIGHT  -  (HEIGHT_PLAYER + 1);
}


