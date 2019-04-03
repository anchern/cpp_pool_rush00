#include "../includes/includes.h"
#include "classes/Game.hpp"

void	setPlayersOnField(Game &game)
{
	t_location tmp_loc;

	for (int k = 0; k < NUMBEROFPLAYERS; k++)
	{
		if (game.getPlayers()[k].get_location().x < 0)
			continue;
		tmp_loc = game.getPlayers()[k].getLocation();
		for (int i = 0; i < HEIGHT_PLAYER_1; i++)
		{
			for (int j = 0; j < WIDTH_PLAYER_1 - 1; j++)
			{
				if (game.getPlayers()[k]._avatar[i][j] != ' ')
				{
					if (game.getGameEntitys(tmp_loc.y + i, tmp_loc.x + j) !=
						NULL)
						checkCollision(game.getGameEntitys(tmp_loc.y + i,
										tmp_loc.x + j),
										(GameEntity *) &game.getPlayers()[i],
										game);
					else
						game.setGameEntitys(tmp_loc.y + i, tmp_loc.x + j,
										&game.getPlayers()[k]);
				}
			}
		}
	}
}

void	setStandardUnitsOnField(Game &game)
{
	t_location tmp_loc;

	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x < 0)
			continue ;
		tmp_loc = game.getStandartUnits()[i].get_location();
		for (int j = 0; j < HEGHT_STANDARD_UNIT; j++)
		{
			for (int k = 0; k < WIDTH_STANDARD_UNIT - 1; k++)
			{
				if (game.getStandartUnits()[i].avatar[j][k] != ' ')
				{
					if (game.getGameEntitys(tmp_loc.y + j, tmp_loc.x + k) !=
							NULL)
						checkCollision(game.getGameEntitys(tmp_loc.y + j, tmp_loc.x +
						k), (GameEntity *)&game.getStandartUnits()[i], game);
					else
						game.setGameEntitys(tmp_loc.y + j, tmp_loc.x + k,
										&game.getStandartUnits()[i]);
				}
			}
		}
	}
}

void	setBulletsOnField(Game &game)
{
	t_bullet	*bullet;
	t_location tmp_loc;

	bullet = game.getBullets();
	while (bullet != nullptr)
	{
		tmp_loc = bullet->bullet->get_location();
		if (game.getGameEntitys(tmp_loc.y , tmp_loc.x)
		!=
		NULL)
			checkCollision(game.getGameEntitys(tmp_loc.y, tmp_loc.x),
					(GameEntity *)bullet->bullet, game);
		game.setGameEntitys(tmp_loc.y, tmp_loc.x, bullet->bullet);
		bullet = bullet->next;
	}
}

void	setEntitiesOnField(Game &game)
{
	setStandardUnitsOnField(game);
	setBulletsOnField(game);
	setPlayersOnField(game);
}


void	setEntitiesOnPrintField(Game &game)
{
	t_location tmp_loc;
	t_bullet	*bullet;

	tmp_loc = game.getPlayers()[0].getLocation();
	bullet = game.getBullets();
	for (int i = 0; i  < HEIGHT_PLAYER_1; i++)
	{
		for (int j = 0; j < WIDTH_PLAYER_1 - 1; j++)
		{
			if (game.getPlayers()[0]._avatar[i][j] != ' ')
				game.setFieldElem(tmp_loc.y + i, tmp_loc.x + j,
								  game.getPlayers()[0]._avatar[i][j]);
		}
	}
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x < 0)
			continue ;
		tmp_loc = game.getStandartUnits()[i].get_location();
		for (int j = 0; j < HEGHT_STANDARD_UNIT; j++)
		{
			for (int k = 0; k < WIDTH_STANDARD_UNIT - 1; k++)
			{
				if (game.getStandartUnits()[i].avatar[j][k] != ' ')
					game.setFieldElem(tmp_loc.y + j, tmp_loc.x + k,
							game.getStandartUnits()[i].avatar[j][k]);
			}
		}
	}
	while (bullet != nullptr)
	{
		tmp_loc = bullet->bullet->get_location();
		game.setFieldElem(tmp_loc.y, tmp_loc.x, bullet->bullet->get_type());
		bullet = bullet->next;
	}
}
