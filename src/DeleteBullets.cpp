/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteBullets.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:33:07 by dlewando          #+#    #+#             */
/*   Updated: 2019/03/28 15:47:55 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Bullet.hpp"

void free_bullets(t_bullet *bullet)
{
	if (bullet == nullptr)
		return ;
	free_bullets(bullet->next);
	delete bullet->bullet;
	delete bullet;
}

void	delete_bullet(t_bullet *bullet,
					  t_bullet *deleted_elem)
{
	t_bullet *previous_elem = nullptr;

	while (bullet != nullptr)
	{
		if (bullet->bullet == deleted_elem->bullet)
		{
			delete bullet->bullet;
			if (previous_elem == nullptr)
			{
				previous_elem = bullet;
				bullet = bullet->next;
				delete previous_elem;
				return;
			}
			else
			{
				previous_elem->next = bullet->next;
				delete bullet;
				return;
			}
		}
		previous_elem = bullet;
		bullet = bullet->next;
	}
}

