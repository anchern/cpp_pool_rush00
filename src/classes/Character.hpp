//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_CHARACTER_HPP
#define C_POOL_CHARACTER_HPP

#include "Bullet.hpp"
#include "GameEntity.hpp"

class Character : public GameEntity
{
public:
	virtual t_bullet *shot(t_bullet *bullets_list) = 0;
	virtual void takeDamage(Bullet &bullet) = 0;


public:
	void set_hp(unsigned int _hp);

	unsigned int get_maxHp() const;

protected:
public:
	unsigned int get_hp() const;

protected:
	unsigned _hp = 0;
	unsigned _maxHp = 0;
};


#endif //C_POOL_CHARACTER_HPP
