
#include "classes/Bullet.hpp"

Bullet *default_bullet_elem(t_location const &location)
{
	Bullet *bullet = new Bullet('-', location, 1);
	return (bullet);
}

t_bullet	*push_bullet_front(t_bullet *bullet, Bullet *bullet1)
{
	t_bullet *new_elem_list;

	if (bullet == nullptr)
	{
		bullet = new t_bullet;
		bullet->bullet = bullet1;
		bullet->next = nullptr;
		return (bullet);
	}
	new_elem_list = new t_bullet;
	new_elem_list->bullet = bullet1;
	new_elem_list->next = bullet;
	bullet = new_elem_list;
	return (bullet);
}
