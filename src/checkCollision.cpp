/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkCollision.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:18:51 by dlewando          #+#    #+#             */
/*   Updated: 2019/04/04 05:43:19 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
#include "classes/Game.hpp"


void	checkCollision(GameEntity *GE1, GameEntity *GE2, Game &game)
{
	int damageGE1;
	int damageGE2;

	if (GE1->get_location().x < 0 || GE2->get_location().x < 0)
		return;
	damageGE1 = GE1->get_damage();
	damageGE2 = GE2->get_damage();
	if (damageGE1 >= 0 && damageGE2 < 0)
	{
		((Character *)GE2)->takeDamage(*((Bullet *)GE1));
		((Bullet *)GE1)->death();
		((Bullet *)GE1)->set_damage(0);
	}
	if (damageGE1 < 0 && damageGE2 >= 0)
	{
		((Character *)GE1)->takeDamage(*((Bullet *)GE2));
		((Bullet *)GE2)->death();
		((Bullet *)GE2)->set_damage(0);
	}
	if (damageGE1 < 0 && damageGE2 < 0)
	{
		((Character *)GE1)->death();
		((Character *)GE2)->death();
	}
	if (damageGE1 >= 0 && damageGE2 >= 0)
	{
		((Bullet *)GE1)->death();
		((Bullet *)GE2)->death();
	}

}