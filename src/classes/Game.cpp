//
// Created by Denis LEWANDOWSKI on 2019-03-28.
//

#include "Game.hpp"

Game& Game::instance()
{
	static Game game;
	return game;
}

Player &Game::getPlayers(int i)
{
	return players[i];
}

const StandartUnit *Game::getStandartUnits() const
{
	return StandartUnits;
}

t_bullet *Game::getBullets() const
{
	return bullets;
}

char &Game::getField(int i, int j)
{
	return (field[i][j]);
}

GameEntity* Game::getGameEntitys(int i, int j) const
{
	return (gameEntitys[i][j]);
}