#include "classes/Game.hpp"

void	initGame(Game &game, const std::string &player_name_1)
{
	t_location location = game.getPlayers()[0].get_location();
	location.x += ((WIDTH_PLAYER_1 - 1) / 2);
	Weapon weapon(location, 'A');
	game.getPlayers()[0].setName(player_name_1);

	game.getPlayers()[0].setWeapon(weapon, 0);

}