//
// Created by Denis LEWANDOWSKI on 2019-04-17.
//

#include "../includes/includes.h"
#include <ncurses.h>

#include <thread>
#include "classes/Game.hpp"


#include <unistd.h>




void	player1Action(int &getch_ref, Game &game, std::thread &thr1, bool &mut_flag)
{
	int saveDegrees;
	std::string pause_items[PAUSE_ITEM] = {	"RESUME GAME",
											   "EXIT"};

	while (true)
	{
		switch (getch_ref)
		{
			case 27:
				switch (menu(pause_items, PAUSE_ITEM))
				{
					case 1:
						break;
					case 2:
						clear();
						printw("BYE!");
						refresh();
						usleep(100000);
						endwin();
						thr1.detach();
						exit(0);
					default:
						break;
				}
				mut_flag = false;
				break;
			case KEY_UP:
				game.getPlayers()[0].set_degrees(90);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_DOWN:
				game.getPlayers()[0].set_degrees(270);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_RIGHT:
				game.getPlayers()[0].set_degrees(180);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_LEFT:
				game.getPlayers()[0].set_degrees(0);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case ' ':
				setPlayersOnField(game);
				saveDegrees = game.getPlayers()[0].get_degrees();
				game.getPlayers()[0].set_degrees(90);
				game.setBullets(game.getPlayers()[0].shot(game.getBullets()));
				game.getPlayers()[0].set_degrees(saveDegrees);
				break;
			default:
				setPlayersOnField(game);
		}
		getch_ref = 0;
		usleep(500);
	}
}
