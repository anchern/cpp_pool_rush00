/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteBullets.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:33:07 by dlewando          #+#    #+#             */
/*   Updated: 2019/04/04 02:41:04 by dlewando         ###   ########.fr       */
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

t_bullet	*delete_bullet(t_bullet *bullet,
					  Bullet *bullet1)
{
	t_bullet *previous_elem = nullptr;
	t_bullet *tmp = bullet;

	while (bullet != nullptr)
	{
		if (bullet->bullet == bullet1)
		{
			delete bullet->bullet;
			if (previous_elem == nullptr)
			{
				previous_elem = bullet;
				bullet = bullet->next;
				delete previous_elem;
				return (bullet);
			}
			else
			{
				previous_elem->next = bullet->next;
				delete bullet;
				bullet = previous_elem->next;
				return (tmp);
			}
		}
		previous_elem = bullet;
		bullet = bullet->next;
	}
	return (tmp);
}

