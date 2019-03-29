#include "../includes/includes.h"
#include "classes/Game.hpp"

void	setEntitiesOnField(Game &game)
{
	t_location tmp_loc;
	t_bullet	*bullet;

	tmp_loc = game.getPlayers(0).getLocation();
	bullet = game.getBullets();
	for (int i = 0; i  < HEIGHT_PLAYER_1; i++)
	{
		for (int j = 0; j < WIDTH_PLAYER_1 - 1; j++)
		{
			if (game.getPlayers(0)._avatar[i][j] != ' ')
				game.setGameEntitys(tmp_loc.y + i, tmp_loc.x + j,
						&game.getPlayers(0));
		}
	}
	while (bullet != nullptr)
	{
		tmp_loc = bullet->bullet->get_location();
		game.setGameEntitys(tmp_loc.y, tmp_loc.x, bullet->bullet);
		bullet = bullet->next;
	}

}

void	setEntitiesOnPrintField(Game &game)
{
	t_location tmp_loc;
	t_bullet	*bullet;

	tmp_loc = game.getPlayers(0).getLocation();
	bullet = game.getBullets();
	for (int i = 0; i  < HEIGHT_PLAYER_1; i++)
	{
		for (int j = 0; j < WIDTH_PLAYER_1 - 1; j++)
		{
			if (game.getPlayers(0)._avatar[i][j] != ' ')
				game.setFieldElem(tmp_loc.y + i, tmp_loc.x + j,
								  game.getPlayers(0)._avatar[i][j]);
		}
	}
	while (bullet != nullptr)
	{
		tmp_loc = bullet->bullet->get_location();
		game.setFieldElem(tmp_loc.y, tmp_loc.x, bullet->bullet->get_type());
		bullet = bullet->next;
	}

}
