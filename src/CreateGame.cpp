#include "Game.hpp"

void	initGame(Game &game, const std::string &player_name_1)
{
	game.getPlayers(0).setName(player_name_1);

}