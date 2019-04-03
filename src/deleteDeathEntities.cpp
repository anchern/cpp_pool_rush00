
#include "../includes/includes.h"
#include "classes/Game.hpp"

void	deleteDeathEntities(Game &game)
{
	t_bullet *bullet;

	bullet = game.getBullets();
	for (int i = 0; i < NUMBEROFPLAYERS; i++)
	{
		if (game.getPlayers()[i].get_hp() == 0)
			game.getPlayers()[i].death();
	}
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_hp() == 0)
			game.getStandartUnits()[i].death();
	}
}