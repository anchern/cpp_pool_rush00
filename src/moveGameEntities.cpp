/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveGameEntities.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 01:34:36 by dlewando          #+#    #+#             */
/*   Updated: 2019/04/03 23:56:13 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
#include "classes/Game.hpp"

void movePlayer(Game &game)
{
	Player *getPlayers;
	
	getPlayers = game.getPlayers();
	for(int i = 0; i < NUMBEROFPLAYERS; i++)
	{
		if (getPlayers[i].get_location().x >= 0)
			getPlayers[i].move(getPlayers[i].get_degrees());
	}
}

void moveBullets(Game &game)
{
	t_bullet *getBullets;

	getBullets = game.getBullets();
	while (getBullets != nullptr)
	{
		getBullets->bullet->move(getBullets->bullet->get_degrees());
		getBullets = getBullets->next;
	}
}


void moveStantardUnits(Game &game)
{
	StandardUnit *getUnits;

	getUnits = game.getStandartUnits();
	for(int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (getUnits[i].get_location().x >= 0)
			getUnits[i].move(getUnits[i].get_degrees());
	}
}
