#include "classes/Game.hpp"
#include <iostream>
#include "ncurses.h"

int main()
{
	int i = 0;
	Game &game = Game::instance();
	int saveDegrees;

	initGame(game, "Kek");
	standardUnitGeneration(game);
	while (true)
	{
		game.clsField();
		game.clsGameEntities();
		setEntitiesOnField(game);

		setEntitiesOnPrintField(game);
		std::cout << "----------------------------------------------------"
		<< std::endl;
		game.printField();
		std::cout << "----------------------------------------------------"
				  << std::endl;
		switch (getchar())
		{
			case 'w':
				game.getPlayers()[0].set_degrees(90);
				movePlayer(game);
				break ;
			case 's':
				game.getPlayers()[0].set_degrees(270);
				movePlayer(game);
				break ;
			case 'd':
				game.getPlayers()[0].set_degrees(180);
				movePlayer(game);
				break ;
			case 'a':
				game.getPlayers()[0].set_degrees(0);
				movePlayer(game);
				break ;
			case ' ':
				saveDegrees = game.getPlayers()[0].get_degrees();
				game.getPlayers()[0].set_degrees(90);
				game.setBullets(game.getPlayers()[0].shot(game.getBullets()));
				game.getPlayers()[0].set_degrees(saveDegrees);
				break ;
			case 'q':
				return (0);
			default:
				break;
		}
		moveStantardUnits(game);
		moveBullets(game);
		i++;
	}
}