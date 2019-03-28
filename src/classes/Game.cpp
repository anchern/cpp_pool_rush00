//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#include "Game.hpp"

Game& Game::instance()
{
	static Game game;
	return game;
}