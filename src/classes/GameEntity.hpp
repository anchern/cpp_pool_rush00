//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_GAMEENTITY_HPP
#define C_POOL_GAMEENTITY_HPP

#include "../../includes/includes.h"


class GameEntity
{
public:
	virtual GameEntity *getType() = 0;
	void		move(int degrees);

	int get_speed() const;

	void set_degrees(int _degrees);

	unsigned int get_damage() const;

	int get_degrees() const;

	const t_location &get_location() const;

	void set_speed(int _speed);

protected:
	t_location	_location;
	unsigned	_damage = 0;
	int			_degrees = 0;
	int			_speed = 1;
};


#endif
