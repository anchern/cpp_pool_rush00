/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkCollision.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:18:51 by dlewando          #+#    #+#             */
/*   Updated: 2019/03/30 05:37:22 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
#include "classes/Game.hpp"


void	checkCollision(GameEntity *GE1, GameEntity *GE2, Game &game)
{
	unsigned int damageGE1;
	unsigned int damageGE2;

	damageGE1 = GE1->get_damage();
	damageGE2 = GE2->get_damage();
	if (damageGE1 > 0 and damageGE2 == 0)
	{
		((Character *)GE2)->takeDamage(*((Bullet *)GE1));
		delete_bullet(game.getBullets(), (Bullet *)GE1);
	}
	if (damageGE1 == 0 and damageGE2 > 0)
	{
		((Character *)GE1)->takeDamage(*((Bullet *)GE2));
		delete_bullet(game.getBullets(), (Bullet *)GE2);
	}
	if (damageGE1 == 0 && damageGE2 == 0)
	{
		((Character *)GE1)->set_hp(0);
		((Character *)GE2)->set_hp(0);
	}
	if (damageGE1 > 0 && damageGE2 > 0)
	{
		delete_bullet(game.getBullets(), (Bullet *)GE1);
		delete_bullet(game.getBullets(), (Bullet *)GE2);
	}

}