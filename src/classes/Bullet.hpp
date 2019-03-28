//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_BULLET_HPP
#define C_POOL_BULLET_HPP

#include "../../includes/includes.h"
#include "GameEntity.hpp"


class Bullet: public GameEntity
{
public:
	Bullet(char _type, t_location const &location,
			unsigned damage);
	Bullet();

	unsigned int get_damage() const;
	const t_location &get_location() const;
	void set_location(const t_location &_location);
	void setDegrees(int degrees);

	char get_type() const;

	GameEntity *getType();

	~Bullet() = default;
private:
	char		_type;
};


#endif //C_POOL_BULLET_HPP
