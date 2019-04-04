//
// Created by Denis LEWANDOWSKI on 2019-03-25.
//

#include "Character.hpp"

//#include "Character.hpp"
void Character::set_hp(unsigned int _hp)
{
	Character::_hp = _hp;
}

unsigned int Character::get_hp() const
{
	return _hp;
}

unsigned int Character::get_maxHp() const
{
	return _maxHp;
}
