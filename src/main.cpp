#include "classes/Game.hpp"
#include <iostream>
#include "ncurses.h"

int main()
{
	Game &game = Game::instance();
	initGame(game, "Kek");
	game.setBullets(game.getPlayers(0).shot(game.getBullets()));
	setEntitiesOnPrintField(game);
	std::cout << "Player: " << game.getPlayers(0).get_name() << std::endl;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			std::cout << game.getField(i, j);
		std::cout << std::endl;
	}
	initscr();
	int a = getch();
	int b = getch();
	int c = getch();
	int d = getch();
	printw("%i %i %i %i", a, b, c, d);
	getch();
	endwin();

	return (0);
}