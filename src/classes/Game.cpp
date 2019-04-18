#include <sstream>
#include "Game.hpp"
#include "ncurses.h"

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
		printw("%s\n", i);
	refresh();
//		std::cout << i << std::endl;
}

void Game::clsGameEntities()
{
	for (auto &i : gameEntities)
		for (auto &j : i)
			j = nullptr;
}

void Game::setScore(unsigned int score)
{
	Game::score += score;
}

unsigned int Game::getScore() const
{
	return score;
}

char *Game::getOneLineField()
{
	char *oneLineField = new char[HEIGHT * (WIDTH + 1)];
	int k = 0;

	for (int i = 0;  i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			oneLineField[k] = field[i][j];
			k++;
		}
		oneLineField[k] = '\n';
		k++;
	}
	oneLineField[k - 1] = 0;
	return oneLineField;
}


