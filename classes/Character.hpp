//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_CHARACTER_HPP
#define C_POOL_CHARACTER_HPP

#include "Bullet.hpp"

class Character
{
	virtual void shot() = 0;
	virtual void death() = 0;
	virtual void takeDamage(Bullet bullet) = 0;
};


#endif //C_POOL_CHARACTER_HPP
