#include "Game.hpp"

Game::Game()
{
	bullets = nullptr;
	clsField();

}

Game& Game::instance()
{
	static Game game;
	return game;
}

Player *Game::getPlayers()
{
	return players;
}

StandardUnit *Game::getStandartUnits()
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
	return (gameEntities[i][j]);
}

void Game::setBullets(t_bullet *bullets)
{
	Game::bullets = bullets;
}

void Game::setGameEntitys(int i, int j, GameEntity *gameEntity)
{
	this->gameEntities[i][j] = gameEntity;
}


void Game::setFieldElem(int i, int j,char c)
{
	field[i][j] = c;
}

void Game::clsField()
{
	for (auto &i : field)
	{
		for (char &j : i)
			j = ' ';
		i[WIDTH] = 0;
	}

}

void Game::printField()
{
	for (auto &i : field)
		std::cout << i << std::endl;
}

void Game::clsGameEntities()
{
	for (auto &i : gameEntities)
		for (auto &j : i)
			j = nullptr;
}

