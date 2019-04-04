
#include "../includes/includes.h"
#include "classes/Game.hpp"

void	standardUnitGeneration(Game &game)
{
	time_t		time1;
	int			rand;
	t_location	location;

//	std::ctime(&time1);
//	std::srand(unsigned(time1));
	rand = std::rand() % (WIDTH - WIDTH_STANDARD_UNIT - 1);
	location.x = rand;
	location.y = 0;
	for (int i = 0; i < STANDART_UNITS_NUMBER ;i++)
	{
		if (game.getStandartUnits()[i].get_location().x == -1)
		{
			game.getStandartUnits()[i].setLocation(location);
			game.getStandartUnits()[i].set_hp(
			game.getStandartUnits()[i].get_maxHp());
			break;
		}
	}

}
