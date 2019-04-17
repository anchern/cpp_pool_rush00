
#include "../includes/includes.h"
#include "classes/Game.hpp"

void	delete_and_move_death_bullets(Game &game)
{
	t_bullet *bulletTmp;
	t_bullet *bulletTmp1;

	bulletTmp = game.getBullets();
	bulletTmp1 = bulletTmp;
	while (bulletTmp != nullptr)
	{
		if (bulletTmp->bullet->get_location().x == -1)
		{
			bulletTmp1 = delete_bullet(bulletTmp1, bulletTmp->bullet);
			bulletTmp = bulletTmp1;
			continue ;
		}
		bulletTmp = bulletTmp->next;
	}
	game.setBullets(bulletTmp1);
	if (game.getBullets() != nullptr)
	{
		for (int i = 0; i < game.getBullets()->bullet->get_speed(); i++)
		{
			moveBullets(game);
			setBulletsOnField(game);
			if (game.getBullets() == nullptr)
				break ;
		}
	}
}

void	standardUnitActions(int j, Game &game)
{
	if (j % 23 == 0)
	{
		for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
			if (game.getStandartUnits()[i].get_location().x != -1)
				game.setBullets(game.getStandartUnits()[i].shot(game.getBullets()));
	}
	else
	{
		for (int i = 0; i < game.getStandartUnits()->get_speed(); i++)
		{
			moveStantardUnits(game);
			setStandardUnitsOnField(game);
		}
	}
}
