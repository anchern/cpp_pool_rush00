//
// Created by Denis LEWANDOWSKI on 2019-04-15.
//

#include "../includes/includes.h"
#include "ncurses.h"
#include "classes/Game.hpp"


void score_calc(Game &game)
{
	int number_of_units = 0;
	int number_of_units_tmp = 0;
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x != -1)
			number_of_units++;
	}
	for (int i = 0; i < NUMBEROFPLAYERS; i++)
		if (game.getPlayers()[i].get_hp() == 0)
			game.getPlayers()[i].death();
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
		if (game.getStandartUnits()[i].get_hp() == 0)
			game.getStandartUnits()[i].death();
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x != -1)
			number_of_units_tmp++;
	}
	if (number_of_units - number_of_units_tmp > 0)
		game.setScore(number_of_units - number_of_units_tmp);
}

void	printField(Game &game, time_t sTime)
{
	time_t time;

	std::time(&time);
	clear();
	printw("Player: %s | HP: %d | Time: %.2d:%.2d | Score: %u\n",game.getPlayers()[0].get_name().c_str(),
		   game.getPlayers()[0].get_hp(), (time - sTime) /60,(time - sTime) % 60, game.getScore());
	for (int k = 0; k < WIDTH; k++)
		printw("-");
	printw("\n");
	game.printField();
	for (int k = 0; k < WIDTH; k++)
		printw("-");
	printw("\n");
	refresh();
}
