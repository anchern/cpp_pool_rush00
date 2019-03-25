//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_BULLET_HPP
#define C_POOL_BULLET_HPP

#include "../includes/includes.h"
#include "GameEntity.hpp"

class Bullet: public GameEntity
{
public:
	explicit Bullet(unsigned damage = 1, char _type = '*');

	unsigned int get_damage() const;

	const t_location &get_location() const;

	void set_location(const t_location &_location);

	void move(int degrees);

	GameEntity *getType();

private:
	unsigned	_damage;
	char		_type;
	t_location 	_location;
};


#endif //C_POOL_BULLET_HPP
