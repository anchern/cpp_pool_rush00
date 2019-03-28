//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#ifndef C_POOL_GAMEENTITY_HPP
#define C_POOL_GAMEENTITY_HPP


class GameEntity
{
public:
	virtual GameEntity *getType() = 0;
	virtual void move(int degrees) = 0;

protected:
	unsigned _damage;
	short	 vector;
};


#endif //C_POOL_GAMEENTITY_HPP
