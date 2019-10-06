//
// Created by Denis LEWANDOWSKI on 2019-04-18.
//

#include "classes/Game.hpp"

void score_calculation(Game &game)
{
	int number_of_units = 0;
	int number_of_units_tmp = 0;
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x != -1)
			number_of_units++;
	}
	for (int i = 0; i < numberOfPlayers; i++)
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