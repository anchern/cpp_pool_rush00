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

void Game::setBullets(t_bullet *bullets)
{
	Game::bullets = bullets;
}

void Game::setGameEntitys(int i, int j, GameEntity *gameEntity)
{
	this->gameEntitys[i][j] = gameEntity;
}

void Game::convertGEtoGF()
{
	Character *player;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (gameEntitys[i][j] != nullptr)
			{
				player = dynamic_cast<Character *>(gameEntitys[i][j]);

			}
		}
	}
}

void Game::setFieldElem(int i, int j,char c)
{
	field[i][j] = c;
}
