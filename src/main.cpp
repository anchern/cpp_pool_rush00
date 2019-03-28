#include "Game.hpp"
#include <iostream>

int main()
{
	Game &game = Game::instance();
	initGame(game, "Kek");
	std::cout << "Player: " << game.getPlayers(0).get_name() << std::endl;
	for (auto &i : game.getPlayers(0)._avatar)
		std::cout << i << std::endl;
	return (0);
}