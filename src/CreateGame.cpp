#include "classes/Game.hpp"
#include <ncurses.h>
void	initSingleGame(Game &game, const std::string &player_name_1)
{
	t_location location;

	location = game.getPlayers()[0].get_location();
	location.x = WIDTH / 2 - WIDTH_PLAYER_1 / 2;
	game.getPlayers()[0].set_location(location);

	location.x += ((WIDTH_PLAYER_1 - 1) / 2);
	Weapon weapon(location, 'A');
	game.getPlayers()[0].setName(player_name_1);

	game.getPlayers()[0].setWeapon(weapon, 0);

}

void	initMultiGame(Game &game, const std::string &player_name_1, const std::string &player_name_2)
{
	t_location location;

//	PLAYER 1
	location = game.getPlayers()[0].get_location();
	location.x = WIDTH / 4 - WIDTH_PLAYER_1 / 2;
	game.getPlayers()[0].set_location(location);

	location.x += ((WIDTH_PLAYER_1 - 1) / 2);
	Weapon weapon(location, 'A');
	game.getPlayers()[0].setName(player_name_1);

	game.getPlayers()[0].setWeapon(weapon, 0);

//  PLAYER 2

	std::string avatar[HEIGHT_PLAYER_1] = {	"  /^\\  ",
										   	"  | |  ",
										   	"/:| |:\\",
										   	"\\4| |2/"};
	game.getPlayers()[1].set_avatar(avatar);

	location = game.getPlayers()[1].get_location();
	location.x = WIDTH - (WIDTH / 4 - WIDTH_PLAYER_1 / 2);
	game.getPlayers()[1].set_location(location);

	location.x += ((WIDTH_PLAYER_1 - 1) / 2);
	Weapon weapon1(location, 'A');
	game.getPlayers()[1].setName(player_name_2);

	game.getPlayers()[1].setWeapon(weapon1, 0);


}

